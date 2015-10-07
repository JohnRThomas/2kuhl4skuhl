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
class GODZILLA_API vrpn
{
public:
	vrpn(std::string object);
	~vrpn();
	int get(double pos[3], double orient[16]);
	Kalman *kalman;
	vrpn_TRACKERCB lastData;

private:
	vrpn_Tracker_Remote *tracker;
	std::string hostname;
	std::string default_host();
	std::string trim_whitespace(std::string str);
};
