// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//VRPN libs
#include "AllowWindowsPlatformTypes.h"
#include <vrpn_Tracker.h>
#include "HideWindowsPlatformTypes.h"
#include <vrpn_quat.h>
#include <string>

#include "kalman.h"

/**
 * 
 */
class GODZILLA_API VRPN
{
public:
	VRPN(FString object, FString host);
	~VRPN();
	int get(double pos[3], double orient[16]);
	Kalman *kalmanX, *kalmanY, *kalmanZ;
	Kalman *kalmanPitch, *kalmanYaw, *kalmanRoll;
	vrpn_TRACKERCB lastData;
	static void VRPN_CALLBACK handle_tracker(void *data, vrpn_TRACKERCB t);

private:
	vrpn_Tracker_Remote *tracker;
	std::string hostname;
	std::string default_host();
	std::string trim_whitespace(std::string str);
};
