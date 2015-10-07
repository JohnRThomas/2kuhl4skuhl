// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "vrpn/vrpn.h"
#include "GameFramework/Actor.h"
#include "VRPNBall.generated.h"

UCLASS()
class GODZILLA_API AVRPNBall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVRPNBall();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	float runTime;
private:
	VRPN* vrpn;
	double pos[3];
	double orient[16];
};
