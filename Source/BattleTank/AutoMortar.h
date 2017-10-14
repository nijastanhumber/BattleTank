// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "AutoMortar.generated.h"

class UTankAimingComponent;
class UTankBarrel;
class UTankTurret;
UCLASS()
class BATTLETANK_API AAutoMortar : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAutoMortar();
	void Fire();

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

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MortarParts", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent *MortarBody;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MortarParts", meta = (AllowPrivateAccess = "true"))
		UTankTurret *MortarDome;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MortarParts", meta = (AllowPrivateAccess = "true"))
		UTankBarrel *MortarBarrel;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MortarParts", meta = (AllowPrivateAccess = "true"))
		UTankAimingComponent *MortarAimingComponent;
	
};
