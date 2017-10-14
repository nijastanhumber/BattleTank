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

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent, Category = "Collision", meta = (AllowPrivateAccess = "true"))
		void OnHit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComponent, FVector NormalImpulse, const FHitResult &Hit);
	void DriveTrack();
	void OnHit_Implementation(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComponent, FVector NormalImpulse, const FHitResult &Hit);

private:
	UTankTrack();

	void ApplySidewaysForce();
	float CurrentThrottle = 0.0f;
};
