// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// -1 is max downward speed, and +1 is max up movement
	void Elevate(float RelativeSpeed);
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup", meta = (BlueprintProtected = "true"))
	float MaxDegreesPerSecond = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup", meta = (BlueprintProtected = "true"))
	float MaxElevationDegrees = 40.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup", meta = (BlueprintProtected = "true"))
	float MinElevationDegrees = 0.0f;
};
