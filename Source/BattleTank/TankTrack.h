// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void SetThrottle(float Throttle);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Setup", meta = (BlueprintProtected = "true"))
		float TrackMaxDrivingForce = 40000000.0f;

private:
	UTankTrack();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
