// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "vrpn/vrpn.h"
#include "GameFramework/Actor.h"
#include "VRPNActor.generated.h"

UCLASS()
class GODZILLA_API AVRPNActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVRPNActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	float runTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VRPN Variables")
	FString Hostname;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VRPN Variables")
	FString TrackerName;

	private:
	VRPN* vrpn;
	double pos[3];
	double orient[16];	
};
