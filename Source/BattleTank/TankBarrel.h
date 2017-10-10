// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// -1 is max downward speed, and +1 is max up movement
	void Elevate(float RelativeSpeed);
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Setup", meta = (BlueprintProtected = "true"))
	float MaxDegreesPerSecond = 10.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Setup", meta = (BlueprintProtected = "true"))
	float MaxElevationDegrees = 40.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Setup", meta = (BlueprintProtected = "true"))
	float MinElevationDegrees = 0.0f;
};
