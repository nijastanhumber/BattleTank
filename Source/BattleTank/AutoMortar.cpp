// Fill out your copyright notice in the Description page of Project Settings.

#include "AutoMortar.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"


// Sets default values
AAutoMortar::AAutoMortar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create static meshes and aiming component
	MortarBody = CreateDefaultSubobject<UStaticMeshComponent>("MortarBody");
	MortarDome = CreateDefaultSubobject<UTankTurret>("MortarDome");
	MortarBarrel = CreateDefaultSubobject<UTankBarrel>("MortarBarrel");

	MortarAimingComponent = CreateDefaultSubobject<UTankAimingComponent>("Aiming Component");

	RootComponent = MortarBody;
	MortarDome->SetupAttachment(MortarBody, FName("Dome"));
	MortarBarrel->SetupAttachment(MortarDome, FName("Barrel"));

	MortarAimingComponent->Initialize(MortarBarrel, MortarDome);
}

// Called when the game starts or when spawned
void AAutoMortar::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAutoMortar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAutoMortar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAutoMortar::AimAt(FVector HitLocation)
{
	if (!ensure(MortarAimingComponent)) { return; }
	MortarAimingComponent->AimAt(HitLocation);
}

void AAutoMortar::Fire()
{
	MortarAimingComponent->Fire();
}

