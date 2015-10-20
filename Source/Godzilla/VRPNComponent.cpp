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
	//UE_LOG(LogTemp, Warning, TEXT("Location(%.2f, %.2f, %.2f)"), x, y, z);
	//UE_LOG(LogTemp, Warning, TEXT("Angle(%.2f, %.2f, %.2f)"), pitch, yaw, roll);
	FVector* NewLocation = new FVector(x, y, 200.0 + z);
	FRotator* NewRotation = new FRotator(pitch, yaw, roll);

	if (x > -300 && x < 300 && y > -300 && y < 300 && z > -300 && z < 300){
		//SetWorldLocationAndRotation(*NewLocation, *NewRotation);
		SetWorldRotation(*NewRotation);
	}
}

