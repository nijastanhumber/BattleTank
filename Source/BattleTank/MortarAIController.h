// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MortarAIController.generated.h"

class AAutoMortar;
class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API AMortarAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	virtual void SetPawn(APawn *InPawn) override;

	virtual void Tick(float DeltaTime) override;
	
private:
	UFUNCTION()
		void OnTankDeath();
	
};
