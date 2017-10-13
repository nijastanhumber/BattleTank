// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "Tank.generated.h"

class UTankAimingComponent;
class UTankBarrel;
class UTankTurret;
class UTankTrack;
class UTankMovementComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
	void Fire();
protected:
	

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void AzimuthTurn(float Rate);
	void LookUp(float Rate);
	void MoveForward(float Value);
	void MoveRight(float Value);

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void AimAt(FVector HitLocation);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TankParts", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent *TankBody;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TankParts", meta = (AllowPrivateAccess = "true"))
		UTankTrack *TankLeftTrack;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TankParts", meta = (AllowPrivateAccess = "true"))
		UTankTrack *TankRightTrack;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TankParts", meta = (AllowPrivateAccess = "true"))
		UTankTurret *TankTurret;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TankParts", meta = (AllowPrivateAccess = "true"))
		UTankBarrel *TankBarrel;
	UPROPERTY()
		class USpringArmComponent *SpringArm;
	UPROPERTY()
		USceneComponent *AzimuthGimbal;
	UPROPERTY()
		class UCameraComponent *TheCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TankParts", meta = (AllowPrivateAccess = "true"))
		UTankAimingComponent *TankAimingComponent;
	UPROPERTY(BlueprintReadOnly, Category = "TankParts", meta = (AllowPrivateAccess = "true"))
		UTankMovementComponent *TankMovementComponent;
};
