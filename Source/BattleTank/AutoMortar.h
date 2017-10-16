// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "AutoMortar.generated.h"

class UTankAimingComponent;
class UTankBarrel;
class UTankTurret;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMortarDelegate);
UCLASS()
class BATTLETANK_API AAutoMortar : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAutoMortar();
	void Fire();

	FMortarDelegate OnDeath;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void AimAt(FVector HitLocation);

	// Called by the engine when actor damage is dealt
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	UFUNCTION(BlueprintPure, Category = "Health")
		float GetHealthPercent() const;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MortarParts", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent *MortarBody;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MortarParts", meta = (AllowPrivateAccess = "true"))
		UTankTurret *MortarDome;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MortarParts", meta = (AllowPrivateAccess = "true"))
		UTankBarrel *MortarBarrel;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MortarParts", meta = (AllowPrivateAccess = "true"))
		UTankAimingComponent *MortarAimingComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Setup", meta = (AllowPrivateAccess = "true"))
		int32 StartingHealth = 60.0f;
	UPROPERTY(VisibleAnywhere, Category = "Health", meta = (AllowPrivateAccess = "true"))
		int32 CurrentHealth;
	
};
