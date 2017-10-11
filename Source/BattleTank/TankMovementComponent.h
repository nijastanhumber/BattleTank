// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;
/**
 * 
 */
UCLASS()
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
	void Initialize(UTankTrack *LeftTrackToSet, UTankTrack *RightTrackToSet);
	void IntendMoveForward(float Throw);
	void IntendMoveRight(float Throw);
	
private:
	UPROPERTY()
	UTankTrack *LeftTrack;
	UPROPERTY()
	UTankTrack *RightTrack;
};
