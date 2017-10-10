// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	void RotateTurret(float RelativeSpeed);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Setup", meta = (BlueprintProtected = "true"))
		float MaxDegreesPerSecond = 25.0f;
	
};
