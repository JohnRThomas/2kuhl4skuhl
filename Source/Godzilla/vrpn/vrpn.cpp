// Fill out your copyright notice in the Description page of Project Settings.

#include "Godzilla.h"
#include "vrpn.h"
#include "vecmat.h"

void VRPN_CALLBACK VRPN::handle_tracker(void *data, vrpn_TRACKERCB t){

	/* Some tracking systems return large values when a point gets
	* lost. If the tracked point seems to be lost, ignore this
	* update. */

	if (Vector::norm(t.pos, 3) > 100)
		return;

	// Store the data in our map so that someone can use it later.
	((VRPN*)data)->lastData = t;
}

VRPN::VRPN(FString object, FString host){
	std::string name(TCHAR_TO_UTF8(*host));
	std::string ob(TCHAR_TO_UTF8(*object));
	UE_LOG(LogTemp, Warning, TEXT("%s: Connecting to VRPN server: %s"), *object, *host);
	
	hostname = name;

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
		UE_LOG(LogTemp, Warning, TEXT("Failed to connect to tracker: %s"), *host);
		tracker = NULL;
	}
	else{
		connection->mainloop();
		std::string fullname = ob + "@" + hostname;

		tracker = new vrpn_Tracker_Remote(fullname.c_str(), connection);

		tracker->register_change_handler((void*)this, handle_tracker);
	}
}

int VRPN::get(double pos[3], double orient[3]){
	/* Set to default values */
	Vector::set(pos, 0, 0, 0);
	Vector::set(orient, 0, 0, 0);

	if (tracker != NULL){
		tracker->mainloop();
		vrpn_TRACKERCB t = lastData;

		//Swap the x and y axis for vrpn->UE4
		pos[0] = t.pos[1];//kalmanX->estimate(t.pos[0]);
		pos[1] = t.pos[0];//kalmanY->estimate(t.pos[2]);
		pos[2] = t.pos[2];//kalmanZ->estimate(t.pos[1]);

		q_vec_type orientd;
		// Convert quaternion into orientation matrix.
		q_to_euler(orientd, t.quat);

		//Swap the pitch and yaw for vrpn->UE4
		orient[0] = 57.295779513*orientd[2];// kalmanYaw->estimate(orientd[1]);
		orient[1] = -57.295779513*orientd[0];// kalmanRoll->estimate(orientd[2]);
		orient[2] = 57.295779513*orientd[1];// kalmanPitch->estimate(orientd[0]);
		return 1;
	}
	else{
		//connect();
	}
	return 0;
}
