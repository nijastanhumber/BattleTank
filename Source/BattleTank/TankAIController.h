// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
protected:	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	// How close can the AI tank get
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Setup", meta = (AllowPrivateAccess = "true"))
	float AcceptanceRadius = 8000.0f;

};
