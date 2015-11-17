// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "vrpn/vrpn.h"
#include "Components/SceneComponent.h"
#include "VRPNComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GODZILLA_API UVRPNComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UVRPNComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VRPN Variables")
	FString Hostname;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VRPN Variables")
	FString TrackerName;

private:
	VRPN* vrpn;
	double pos[3];
	double orient[16];

	
};
