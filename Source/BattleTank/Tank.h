// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "Tank.generated.h"

class UTankAimingComponent;
class UTankBarrel;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	UPROPERTY()
	UTankAimingComponent *TankAimingComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Firing", meta = (BlueprintProtected = "true"))
	float LaunchSpeed = 100000.0f; // TODO find sensible default

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void AzimuthTurn(float Rate);
	void LookUp(float Rate);

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Setup")

	void AimAt(FVector HitLocation);

private:
	UPROPERTY()
		UStaticMeshComponent *TankBody;
	UPROPERTY()
		UStaticMeshComponent *TankLeftTrack;
	UPROPERTY()
		UStaticMeshComponent *TankRightTrack;
	UPROPERTY()
		UStaticMeshComponent *TankTurret;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TankParts", meta = (AllowPrivateAccess = "true"))
		UTankBarrel *TankBarrel;
	UPROPERTY()
		class USpringArmComponent *SpringArm;
	UPROPERTY()
		USceneComponent *AzimuthGimbal;
	UPROPERTY()
		class UCameraComponent *TheCamera;
	
};
