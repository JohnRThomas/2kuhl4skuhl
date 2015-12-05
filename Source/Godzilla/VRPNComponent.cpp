// Fill out your copyright notice in the Description page of Project Settings.

#include "Godzilla.h"
#include "VRPNComponent.h"
#include "vrpn/vrpn.h"
#include <string>


// Sets default values for this component's properties
UVRPNComponent::UVRPNComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
	Hostname = FString(TEXT("localhost"));
	TrackerName = FString(TEXT("test"));
}

// Called when the game starts
void UVRPNComponent::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("%s: Connecting..."), *TrackerName);
	vrpn = new VRPN(TrackerName, Hostname);
}

// Called every frame
void UVRPNComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	vrpn->get(pos, orient);
	double x = 100.0 * pos[0];
	double y = 100.0 * pos[1];
	double z = 100.0 * pos[2];
	double pitch = orient[0];
	double yaw = orient[1];
	double roll = orient[2];
	FVector NewLocation = FVector(x, y, 200.0 + z);
	FRotator NewRotation = FRotator(pitch, yaw, roll);

	float DeltaHeight = (FMath::Sin(runTime + DeltaTime) - FMath::Sin(runTime));
	NewLocation.X = x;
	NewLocation.Y = y;
	NewLocation.Z = 200.0 + z + DeltaHeight * 20.0f;
	NewRotation.Pitch = pitch;
	NewRotation.Yaw = yaw;
	NewRotation.Roll = roll;
	runTime += DeltaTime;
	if (x > -300 && x < 300 && y > -300 && y < 300 && z > -300 && z < 300){
		SetWorldLocationAndRotation(NewLocation, NewRotation);
	}

	TransformVector = NewLocation;
	RotationMatrix = NewRotation;
}

