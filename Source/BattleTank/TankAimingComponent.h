// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Enum for aiming state
UENUM()
enum class EFiringState : uint8
{
	Locked,
	Aiming,
	Reloading,
	OutOfAmmo
};

class UTankBarrel;
class UTankTurret;
class AProjectile;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void Initialize(UTankBarrel *BarrelToSet, UTankTurret *TurretToSet);

	EFiringState GetFiringState() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringState FiringState = EFiringState::Reloading;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Setup", meta = (BlueprintProtected = "true"))
		TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Firing", meta = (BlueprintProtected = "true"))
		float LaunchSpeed = 8000.0f;

public:	
	void AimAt(FVector HitLocation);

	void Fire();

	UFUNCTION(BlueprintCallable, Category = "Firing")
	int32 GetRoundsLeft() const;
	
private:
	UPROPERTY()
		UTankBarrel *Barrel;
	UPROPERTY()
		UTankTurret *Turret;

	UPROPERTY(EditDefaultsOnly, Category = "Setup", meta = (AllowPrivateAccess = "true"))
		float ReloadTime = 3.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup", meta = (AllowPrivateAccess = "true"))
		double LastFireTime = 0.0f;

	UPROPERTY()
		FVector AimDirection;

	UPROPERTY(EditDefaultsOnly, Category = "Setup", meta = (AllowPrivateAccess = "true"))
	int32 RoundsLeft = 20;

	void MoveBarrelTowards(FVector AimDirection);
	bool IsBarrelMoving();
};
