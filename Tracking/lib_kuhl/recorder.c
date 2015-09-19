/*
 * This is a simple program that will read from the VRPN
 * server set in the home directory and print the entries 
 * it reads to stdout.
 *
 * @author John Thomas
 * @LastModified September 2015
 */ 
#include <stdio.h>
#include <stdlib.h>

#ifdef __APPLE__
#include <unistd.h>
#endif

#include "vrpn-help.h"

#if defined(_WIN32)
#define usleep Sleep
#endif

int main(int argc, char* argv[]){

	//Check if we got the proper arguments.
	if(argc < 2){
	
		printf("Usage\n\trecorder <object name>\n");
		printf("\n");
		printf("This program reads data from a VRPN server and saves it to a file that can be played back later.\n");
		exit(1);
	}
	
	//Buffers for the data.
	float pos[3];
	float rotMat[9];
	char* trackerName = argv[1];
	
	//Loop until Ctrl+C.
	while(1){
	
		//Get the next vrpn entry
		if(vrpn_get(trackerName, NULL, pos, rotMat)){
			printf("x: %.3f y: %.3f z: %.3f\n", pos[0], pos[1], pos[2]);
			usleep(100000);
		}
	}
}
