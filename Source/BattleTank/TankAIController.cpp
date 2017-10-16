// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
// Depends on movement component via pathfinding system

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ATank *PlayerTank = Cast<ATank>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
	ATank *ControlledTank = Cast<ATank>(GetPawn());

	if (!ensure(PlayerTank) || !ensure(ControlledTank)) { return; }

	// Move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius); // TODO check radius is in cm

	// Aim towards the player
	ControlledTank->AimAt(PlayerTank->GetActorLocation());

	// Fire if ready
	UTankAimingComponent *AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	if (AimingComponent->GetFiringState() == EFiringState::Locked)
		ControlledTank->Fire();
}

void ATankAIController::SetPawn(APawn *InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		ATank *PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		// Subscribe our local method to the tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
	}
}

void ATankAIController::OnTankDeath()
{
	if (!ensure(GetPawn())) { return; }
	{
		GetPawn()->DetachFromControllerPendingDestroy();
	}
}

