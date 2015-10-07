// Fill out your copyright notice in the Description page of Project Settings.

#include "Godzilla.h"
#include "vrpn.h"
#include "vecmat.h"
#include <iostream>
#include <fstream>

void VRPN_CALLBACK handle_tracker(void *data, vrpn_TRACKERCB t){

	/* Some tracking systems return large values when a point gets
	* lost. If the tracked point seems to be lost, ignore this
	* update. */
	double pos[3];
	Vector::set(pos, t.pos[0], t.pos[1], t.pos[2]);

	if (Vector::norm(pos, 3) > 100)
		return;

	// Store the data in our map so that someone can use it later.
	vrpn* tracker = (vrpn*)data;
	t.pos[0] = tracker->kalman->estimate(t.pos[0]);
	tracker->lastData = t;
}

vrpn::vrpn(std::string object){
	vrpn::hostname = default_host();

	/* If this is our first time, create a tracker for the object@hostname string, register the callback handler. */
	printf("Connecting to VRPN server: %s\n", hostname);
	// If we are making a TCP connection and the server isn't up, the following function call may hang for a long time
	vrpn_Connection *connection = vrpn_get_connection_by_name(hostname.c_str());

	/* Wait for a bit to see if we can connect. Sometimes we don't immediately connect! */
	for (int i = 0; i<1000 && !connection->connected(); i++)
	{
		Sleep(1);
		connection->mainloop();
	}
	/* If connection failed, exit. */
	if (!connection->connected())
	{
		delete connection;
		printf(("Failed to connect to tracker: " + hostname + "\n").c_str());
		exit(EXIT_FAILURE);
	}


	std::string fullname = object + "@" + hostname;

	tracker = new vrpn_Tracker_Remote(fullname.c_str(), connection);

	tracker->register_change_handler((void*)this, handle_tracker);

	kalman = new Kalman(0.1, 0.1);
}

int vrpn::get(double pos[3], double orient[16]){
	/* Set to default values */
	Vector::set(pos, 10000, 10000, 10000);
	Matrix::identity(orient, 4);

	tracker->mainloop();
	vrpn_TRACKERCB t = lastData;
	double pos4[4];
	for (int i = 0; i<3; i++)
		pos4[i] = t.pos[i];
	pos4[3] = 1;

	double orientd[16];
	// Convert quaternion into orientation matrix.
	q_to_ogl_matrix(orientd, t.quat);
	for (int i = 0; i<16; i++)
		orient[i] = (float)orientd[i];

	/* VICON in the MTU IVS lab is typically calibrated so that:
	* X = points to the right (while facing screen)
	* Y = points into the screen
	* Z = up
	* (left-handed coordinate system)
	*
	* PPT is typically calibrated so that:
	* X = the points to the wall that has two closets at both corners
	* Y = up
	* Z = points to the door
	* (right-handed coordinate system)
	*
	* By default, OpenGL assumes that:
	* X = points to the right (while facing screen in the IVS lab)
	* Y = up
	* Z = points OUT of the screen (i.e., -Z points into the screen in te IVS lab)
	* (right-handed coordinate system)
	*
	* Below, we convert the position and orientation
	* information into the OpenGL convention.
	*/
	if (hostname.length() > 14 && hostname.compare("tcp://141.219.")) // MTU vicon tracker
	{
		double viconTransform[16] = { 
			1, 0, 0, 0,  // column major order!
			0, 0, -1, 0,
			0, 1, 0, 0,
			0, 0, 0, 1 };
		Matrix::mult_vecNd_new(orient, viconTransform, orient, 4);
		Matrix::mult_vecNd_new(pos4, viconTransform, pos4, 4);
		Vector::copy(pos, pos4, 3);
		return 1; // we successfully collected some data
	}
	else // Non-Vicon tracker
	{
		/* Don't transform other tracking systems */
		// orient is already filled in
		Vector::copy(pos, pos4, 3);
		return 1; // we successfully collected some data
	}
	return 0;
}

std::string vrpn::default_host(){
	/* Try reading VRPN server information from ~/.vrpn-server

	This file should contain a single line that says something like:
	tcp://VRPN.SERVER.IP.ADDR
	*/
	std::string path = std::string(std::getenv("HOME")) + "/.vrpn-server";

	std::ifstream f;
	f.open(path, std::ios::in);

	if (!f.is_open())
	{
		printf("Can't open file %s to get VRPN server information.\n", path);
		return NULL;
	}
	std::string vrpnString;

	do
	{
		if (getline(f, vrpnString))
		{
			printf("Can't read %s to get VRPN server information.\n", path);
			return NULL;
		}
		trim_whitespace(vrpnString);
	} while (vrpnString.at(0) == '#' || vrpnString.length() == 0);  // allow for comments and blank lines in vrpn-server file.
	f.close();

	// printf("%s: Found in %s: '%s'\n", __func__, path, vrpnString);
	return vrpnString;
}

std::string vrpn::trim_whitespace(std::string str)
{
	size_t first = str.find_first_not_of(' ');
	size_t last = str.find_last_not_of(' ');
	return str.substr(first, (last - first + 1));

	/* Find first non-whitespace character in string (or the null terminator) 
	char *firstNonSpace = str->c_str();
	while (isspace(*firstNonSpace) && *firstNonSpace != 0)
		firstNonSpace++;

	/* If it was an empty string 
	if (*firstNonSpace == 0)
	{
		*str = "\0";
		return str;
	}

	/* Find the last character in the string 
	char *lastNonSpace = str->c_str() + str->length() - 1;
	while (isspace(*lastNonSpace))
		lastNonSpace--;

	*(lastNonSpace + 1) = 0; // set byte after the last nonspace character to null.

	// If the string is two non-whitespace characters,
	// lastNonSpace-firstNonSpace will be 1. But, we want to copy both
	// of the characters plus the null terminator. 
	memmove(str, firstNonSpace, lastNonSpace - firstNonSpace + 2);
	return str;*/
}

