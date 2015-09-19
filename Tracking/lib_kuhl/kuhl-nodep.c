/* Copyright (c) 2014 Scott Kuhl. All rights reserved.
 * License: This code is licensed under a 3-clause BSD license. See
 * the file named "LICENSE" for a full copy of the license.
 */

/**
   This file is similar to kuhl-util.c, however these are functions
 * that do not depend on any other libraries. Therefore, it should be
 * easy to use this file with other projects.
 */

#define __GNU_SOURCE // make sure are allowed to use GNU extensions. Redundant if compiled with -std=gnu99
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <ctype.h> // isspace()

#ifdef __APPLE__
#include <unistd.h>
#include <sys/time.h>
#elif defined(_WIN32)
#include<Time.h>
struct timeval {
	__int32 tv_sec;
	__int32 tv_usec;
};
#endif


#include "kuhl-nodep.h"


// When compiling on windows, add suseconds_t and the rand48 functions.
#ifdef __MINGW32__
#define RAND48_SEED_0   (0x330e)
#define RAND48_SEED_1 (0xabcd)
#define RAND48_SEED_2 (0x1234)
#define RAND48_MULT_0 (0xe66d)
#define RAND48_MULT_1 (0xdeec)
#define RAND48_MULT_2 (0x0005)
#define RAND48_ADD (0x000b)

unsigned short _rand48_seed[3] = {
		RAND48_SEED_0,
		 RAND48_SEED_1,
		 RAND48_SEED_2
};
unsigned short _rand48_mult[3] = {
		 RAND48_MULT_0,
		 RAND48_MULT_1,
		 RAND48_MULT_2
 };
unsigned short _rand48_add = RAND48_ADD;

void
 _dorand48(unsigned short xseed[3])
 {
			 unsigned long accu;
			 unsigned short temp[2];
	
			 accu = (unsigned long)_rand48_mult[0] * (unsigned long)xseed[0] +
			  (unsigned long)_rand48_add;
			 temp[0] = (unsigned short)accu;        // lower 16 bits 
			 accu >>= sizeof(unsigned short)* 8;
			 accu += (unsigned long)_rand48_mult[0] * (unsigned long)xseed[1] +
			  (unsigned long)_rand48_mult[1] * (unsigned long)xseed[0];
			 temp[1] = (unsigned short)accu;        // middle 16 bits
			 accu >>= sizeof(unsigned short)* 8;
			 accu += _rand48_mult[0] * xseed[2] + _rand48_mult[1] * xseed[1] + _rand48_mult[2] * xseed[0];
			 xseed[0] = temp[0];
			 xseed[1] = temp[1];
			 xseed[2] = (unsigned short)accu;
}

double erand48(unsigned short xseed[3])
{
		 _dorand48(xseed);
		 return ldexp((double) xseed[0], -48) +
				ldexp((double) xseed[1], -32) +
				ldexp((double) xseed[2], -16);
}

double drand48(){
	return erand48(_rand48_seed);
}

void srand48(long seed){
	_rand48_seed[0] = RAND48_SEED_0;
	_rand48_seed[1] = (unsigned short)seed;
	_rand48_seed[2] = (unsigned short)(seed >> 16);
	_rand48_mult[0] = RAND48_MULT_0;
	_rand48_mult[1] = RAND48_MULT_1;
	_rand48_mult[2] = RAND48_MULT_2;
	_rand48_add = RAND48_ADD;
}
#endif

/** Don't call this function, call kuhl_malloc() instead. */
void *kuhl_mallocFileLine(size_t size, const char *file, int line)
{
	if(size == 0)
	{
		fprintf(stderr, "!!!!! malloc Warning !!!!! - Size 0 passed to malloc at %s:%d\n", file, line);
		return NULL;
	}
	void *ret = malloc(size);
	if(ret == NULL)
		fprintf(stderr, "!!!!! malloc Error !!!!! - Failed to allocate %du bytes at %s:%d\n", (int) size, file, line);
	return ret;
}



/** Checks if a file is readable or not by attempting to fopen() the
	file for reading. IMPORTANT: Calling fopen() on a directory is
	undefined---but on Linux fopen() typically behaves as if it were
	successful. Therefore, on Linux, this function will also find
	directories.

 @param filename The file to check
 @return Returns 1 if we can read the file, 0 otherwise.
*/
int kuhl_can_read_file(const char *filename)
{
	FILE *f = fopen(filename, "r");
	if(f == NULL)
		return 0;
	else
	{
		fclose(f);
		return 1;
	}
}

/** Replaces all instances of '\' in a string with '/'. This function
	is useful if you have a relative file path created on a Windows
	machine---and you want to try to open that file on Linux.

	@param input The string to change '\' to '/'
	
	@return A newly allocated string containing a copy of input with
	'\' changed to '/'. The returned string should be free()'d by the
	caller.
*/
static char* kuhl_fix_path(const char* input)
{
	if(input == NULL)
		return NULL;
	
	char *output = strdup(input);
	if(output == NULL) // insufficient memory
	{
		perror("strdup");
		exit(EXIT_FAILURE);
	}
	char *tmp = output;

	while(*tmp != '\0')
	{
		if(*tmp == '\\')
			*tmp = '/';
		tmp++;
	}
	return output;
}

/** Creates a path out of strings a and b (with a '/' inserted between
 * them). Then, checks to see if the path is readable with
 * kuhl_can_read_file().

	@param a The first part of the path.
	@param b The second part of the path.
	@return The new path (if it is readable) or NULL.
*/
static char* kuhl_path_concat_read(const char* a, const char* b)
{
	if(a == NULL || b == NULL)
		return NULL;

	int combinedLen = strlen(a)+strlen(b)+32; // ensure plenty of space
	char *combined = (char*)kuhl_malloc(sizeof(char)*combinedLen);
	int ret = snprintf(combined, combinedLen, "%s/%s", a, b);
	if(ret < 0 || ret >= combinedLen)
	{
		fprintf(stderr, "snprintf() error");
		exit(EXIT_FAILURE);
	}

	if(kuhl_can_read_file(combined))
		return combined;
	else
	{
		free(combined);
		return NULL;
	}
}

static int kuhl_random_init_done = 0; /*< Have we called srand48() yet? */
/** Generates a random integer between min and max inclusive. This
 * uses floating point to avoid possible issues with using rand()
 * along with modulo. This approach isn't completely bias free since
 * doubles don't have infinite precision and we aren't guaranteed
 * perfectly uniform distribution after multiplying the value returned
 * by drand48(). But, this is good enough for most purposes.
 *
 * @param min Smallest random number that we want.
 * @param max Largest random number that we want.
 */
int kuhl_randomInt(int min, int max)
{
	if(kuhl_random_init_done == 0)
	{
		// http://stackoverflow.com/questions/8056371
		srand48((getpid()*2654435761U)^time(NULL));
		kuhl_random_init_done = 1;
	}
	
	int possibleVals = max-min+1;
	double fl = drand48(); // [0, 1.0)
	fl = fl*possibleVals; // [0, possibleVals)
	fl = fl+min;          // [min, min+possibleVals)
						  // [min, min+(max-min+1))
						  // [min, max+1)
	return floor(fl); // casting to int fails to work with negative values
}

/** Shuffles an array of items randomly.

   @param array Array of items
   @param n Number of items in the array.
   @param size Size of each item.
*/
void kuhl_shuffle(void *array, int n, int size)
{
	char *arr = (char*) array; // Use a char array which we know uses 1 byte pointer arithmetic
	char *tmp = (char*)kuhl_malloc(size); // avoid use of VLA

	// https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle
	for(int i=n-1; i>=1; i--)
	{
		int j = kuhl_randomInt(0, i); // index to swap

		// Swap the values
		memcpy(tmp,        arr+j*size, size);
		memcpy(arr+j*size, arr+i*size, size);
		memcpy(arr+i*size, tmp,        size);
	}

	free(tmp);
}

/** Removes any whitespace characters at the beginning or end of the string in place.

	@param str The null-terminated string to trim in place.
	@return The same pointer as the str parameter.
*/
char* kuhl_trim_whitespace(char *str)
{
	/* Find first non-whitespace character in string (or the null terminator) */
	char *firstNonSpace = str;
	while(isspace(*firstNonSpace) && *firstNonSpace != 0)
		firstNonSpace++;

	/* If it was an empty string */
	if(*firstNonSpace == 0)
	{
		*str = 0;
		return str;
	}

	/* Find the last character in the string */
	char *lastNonSpace = str + strlen(str) - 1;
	while(isspace(*lastNonSpace))
		lastNonSpace--;

	*(lastNonSpace+1) = 0; // set byte after the last nonspace character to null.
	
	// If the string is two non-whitespace characters,
	// lastNonSpace-firstNonSpace will be 1. But, we want to copy both
	// of the characters plus the null terminator. */
	memmove(str, firstNonSpace, lastNonSpace-firstNonSpace+2);
	return str;
}

/** Returns the current time in milliseconds. 1 second = 1000
 * milliseconds */
long kuhl_milliseconds()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	long ms = (tv.tv_sec * 1000L) + tv.tv_usec / 1000L;
	return ms;
}

/**
   Generate random numbers following Gaussian distribution. The
   generated numbers will have a mean of 0 and a standard deviation of
   1.

   @return A random sample from a Gaussian distribution.

   Source: http://c-faq.com/lib/gaussian.html
   Discussed in Knuth and described by Marsaglia
 */
double kuhl_gauss()
{
	static double V2;
	static double S;
	static int phase = 0;
	double X;

	if(phase == 0) {
		static double V1;
		do {
			double U1 = (double)rand() / RAND_MAX;
			double U2 = (double)rand() / RAND_MAX;

			V1 = 2 * U1 - 1;
			V2 = 2 * U2 - 1;
			S = V1 * V1 + V2 * V2;
			} while(S >= 1 || S == 0);

		X = V1 * sqrt(-2 * log(S) / S);
	} else
		X = V2 * sqrt(-2 * log(S) / S);

	phase = 1 - phase;

	return X;
}
