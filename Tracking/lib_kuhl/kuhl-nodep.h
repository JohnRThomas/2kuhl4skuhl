/* Copyright (c) 2014 Scott Kuhl. All rights reserved.
 * License: This code is licensed under a 3-clause BSD license. See
 * the file named "LICENSE" for a full copy of the license.
 */

/** @file
 * @author Scott Kuhl
 *
 * This file provides miscellaneous functions which do not depend on
 * any other libraries. When people include kuhl-util.h, this file is
 * also included.
 */


#ifndef __KUHL_NODEP_H__
#define __KUHL_NODEP_H__

// When compiling on windows, add suseconds_t and the rand48 functions.
#ifdef __MINGW32__
#include <windows.h>
typedef long suseconds_t;
#endif

#ifdef __cplusplus
extern "C" {
#endif

/** This structure contains all of a the state necessary for
 * frames-per-second calculations. */
typedef struct
{
	int frame; /**< Number of frames in this second. */
	long timebase; /**< The time in ms that we last updated the FPS
	                * estimate */
	float fps; /**< Current estimate of FPS? */
} kuhl_fps_state;


/** An alternative to malloc() which behaves the same way except it
 * prints a message when common errors occur (out of memory, trying to
 * allocate 0 bytes). */
#define kuhl_malloc(size) kuhl_mallocFileLine(size, __FILE__, __LINE__)


int kuhl_can_read_file(const char *filename);

int kuhl_randomInt(int min, int max);
void kuhl_shuffle(void *array, int n, int size);
char* kuhl_trim_whitespace(char *str);
double kuhl_gauss();


#ifdef __cplusplus
} // end extern "C"
#endif
#endif // __KUHL_NODEP_H__
