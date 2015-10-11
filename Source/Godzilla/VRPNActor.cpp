// Fill out your copyright notice in the Description page of Project Settings.

#include "Godzilla.h"
#include "VRPNActor.h"
#include "vrpn/vrpn.h"
#include <string>

// Sets default values
AVRPNActor::AVRPNActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Hostname = FString(TEXT("localhost"));
	TrackerName = FString(TEXT("test"));
}

// Called when the game starts or when spawned
void AVRPNActor::BeginPlay()
{
	Super::BeginPlay();
	
	vrpn = new VRPN(TrackerName, Hostname);
}

// Called every frame
void AVRPNActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	vrpn->get(pos, orient);
	double x = 100.0 * pos[0];
	double y = 100.0 * pos[1];
	double z = 100.0 * pos[2];
	double pitch = orient[0];
	double yaw = orient[1];
	double roll = orient[2];
	//UE_LOG(LogTemp, Warning, TEXT("Location(%.2f, %.2f, %.2f)"), x, y, z);
	//UE_LOG(LogTemp, Warning, TEXT("Angle(%.2f, %.2f, %.2f)"), pitch, yaw, roll);
	FVector NewLocation = GetActorLocation();
	FRotator NewRotation = GetActorRotation();
	float DeltaHeight = (FMath::Sin(runTime + DeltaTime) - FMath::Sin(runTime));
	NewLocation.X = x;
	NewLocation.Y = y;
	NewLocation.Z = 200.0 + z + DeltaHeight * 20.0f;
	NewRotation.Pitch = pitch;
	NewRotation.Yaw = yaw;
	NewRotation.Roll = roll;
	runTime += DeltaTime;
	if (x > -300 && x < 300 && y > -300 && y < 300 && z > -300 && z < 300){
		SetActorLocationAndRotation(NewLocation, NewRotation);
	}

}

