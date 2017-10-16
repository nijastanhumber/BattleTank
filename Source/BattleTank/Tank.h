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

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);
UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
	void Fire();

	FTankDelegate OnDeath;

protected:
	

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void AzimuthTurn(float Rate);
	void LookUp(float Rate);
	void MoveForward(float Value);
	void MoveRight(float Value);

	void Swap();

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void AimAt(FVector HitLocation);

	// Called by the engine when actor damage is dealt
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;

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
	UPROPERTY()
		UCameraComponent *SecondCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TankParts", meta = (AllowPrivateAccess = "true"))
		UTankAimingComponent *TankAimingComponent;
	UPROPERTY(BlueprintReadOnly, Category = "TankParts", meta = (AllowPrivateAccess = "true"))
		UTankMovementComponent *TankMovementComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		int32 StartingHealth = 100.0f;
	UPROPERTY(VisibleAnywhere, Category = "Health")
		int32 CurrentHealth;
};
