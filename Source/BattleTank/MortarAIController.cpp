// Fill out your copyright notice in the Description page of Project Settings.

#include "MortarAIController.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "AutoMortar.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"

void AMortarAIController::BeginPlay()
{
	Super::BeginPlay();

}

void AMortarAIController::SetPawn(APawn *InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		ATank *PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		// Subscribe our local method to the tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &AMortarAIController::OnTankDeath);
	}
}

void AMortarAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ATank *PlayerTank = Cast<ATank>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
	AAutoMortar *ControlledTank = Cast<AAutoMortar>(GetPawn());

	if (!ensure(PlayerTank) || !ensure(ControlledTank)) { return; }

	 // Aim towards the player
	ControlledTank->AimAt(PlayerTank->GetActorLocation());

	// Fire if ready
	UTankAimingComponent *AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	//if (AimingComponent->GetFiringState() == EFiringState::Locked)
		ControlledTank->Fire();
}

void AMortarAIController::OnTankDeath()
{
	if (!GetPawn()) { return; }
	{
		GetPawn()->DetachFromControllerPendingDestroy();
	}
}


