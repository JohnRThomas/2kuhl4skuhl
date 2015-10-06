// Fill out your copyright notice in the Description page of Project Settings.

#include "Godzilla.h"
#include "vrpn.h"
#include <map>
#include <string>


vrpn::vrpn(){



	kalman = new Kalman(0.1, 0.1);
}

int vrpn::get(const char *object, const char *hostname, float pos[3], float orient[16]){
	//smooth function VVV
	//t.pos[0] = kalman->estimate(t.pos[0]);

	//TODO move functionality to here.
	return 0;
}

char* vrpn::default_host(){
	/* Try reading VRPN server information from ~/.vrpn-server

	This file should contain a single line that says something like:
	tcp://VRPN.SERVER.IP.ADDR
	*/
	const char *homedir = getenv("HOME");
	char path[1024];
	sprintf_s(path, 1024, "%s/.vrpn-server", homedir);
	FILE *f = fopen(path, "r");
	if (f == NULL)
	{
		printf("Can't open file %s to get VRPN server information.\n", path);
		return NULL;
	}
	char *vrpnString = (char*)malloc(1024);
	*vrpnString = '\0';

	do
	{
		if (fgets(vrpnString, 1024, f) == NULL)
		{
			printf("Can't read %s to get VRPN server information.\n", path);
			return NULL;
		}
		trim_whitespace(vrpnString);
	} while (*vrpnString == '#' || strlen(vrpnString) == 0);  // allow for comments and blank lines in vrpn-server file.
	fclose(f);

	// printf("%s: Found in %s: '%s'\n", __func__, path, vrpnString);
	return vrpnString;
}

char* vrpn::trim_whitespace(char *str)
{
	/* Find first non-whitespace character in string (or the null terminator) */
	char *firstNonSpace = str;
	while (isspace(*firstNonSpace) && *firstNonSpace != 0)
		firstNonSpace++;

	/* If it was an empty string */
	if (*firstNonSpace == 0)
	{
		*str = 0;
		return str;
	}

	/* Find the last character in the string */
	char *lastNonSpace = str + strlen(str) - 1;
	while (isspace(*lastNonSpace))
		lastNonSpace--;

	*(lastNonSpace + 1) = 0; // set byte after the last nonspace character to null.

	// If the string is two non-whitespace characters,
	// lastNonSpace-firstNonSpace will be 1. But, we want to copy both
	// of the characters plus the null terminator. */
	memmove(str, firstNonSpace, lastNonSpace - firstNonSpace + 2);
	return str;
}

