// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "TankPlayerController.generated.h"

class ATank;
/**
 * Responsible for helping the player aim.
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	ATank* GetControlledTank() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent *AimCompRef);

	virtual void BeginPlay() override;

//	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Tank", meta = (BlueprintProtected = "true"))
//	TSubclassOf<UUserWidget> HUDWidgetClass;

//	UPROPERTY()
//	UUserWidget *CurrentWidget;

	UPROPERTY(EditDefaultsOnly)
	float CrossHairXLocation = 0.5f;
	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation = 0.333333f;
	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000.0f;

private:
	/** Start the tank moving the barrel so that a shot would hit where the crosshair intersects the world */
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector &OutHitLocation) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation) const;
};
