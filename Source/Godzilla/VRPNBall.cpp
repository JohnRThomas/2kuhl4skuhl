// Fill out your copyright notice in the Description page of Project Settings.

#include "Godzilla.h"
#include "VRPNBall.h"
#include "vrpn/vrpn.h"
#include <string>

// Sets default values
AVRPNBall::AVRPNBall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AVRPNBall::BeginPlay()
{
	Super::BeginPlay();
	vrpn = new VRPN("test");
}

// Called every frame
void AVRPNBall::Tick( float DeltaTime )
{
	Super::Tick(DeltaTime);
	vrpn->get(pos, orient);
	double x = 10.0 * pos[0];
	double y = 10.0 * pos[2];
	double z = 100.0 * pos[1];
	UE_LOG(LogTemp, Warning, TEXT("(%.2f, %.2f, %.2f)"), x, y, z);
	FVector NewLocation = GetActorLocation();
	float DeltaHeight = (FMath::Sin(runTime + DeltaTime) - FMath::Sin(runTime));
	NewLocation.X = x;
	NewLocation.Y = y;
	NewLocation.Z = 200.0 + z + DeltaHeight * 20.0f;
	runTime += DeltaTime;
	if (x > -300 && x < 300 && y > -300 && y < 300 && z > -300 && z < 300){
		SetActorLocation(NewLocation);
	}
}

