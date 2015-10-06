// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//VRPN libs
#include "AllowWindowsPlatformTypes.h"
#include <vrpn_Tracker.h>
#include "HideWindowsPlatformTypes.h"
#include <vrpn_quat.h>

#include "kalman.h"

/**
 * 
 */
class GODZILLA_API vrpn
{
public:
	vrpn();
	~vrpn();
	int get(const char *object, const char *hostname, float pos[3], float orient[16]);

private:
	Kalman *kalman;

	char* default_host();
	char* trim_whitespace(char *str);
};
