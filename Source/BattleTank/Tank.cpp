// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "UObject/ConstructorHelpers.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the static meshes
	TankBody = CreateDefaultSubobject<UStaticMeshComponent>("TankBody");
	TankLeftTrack = CreateDefaultSubobject<UStaticMeshComponent>("TankLeftTrack");
	TankRightTrack = CreateDefaultSubobject<UStaticMeshComponent>("TankRightTrack");
	TankTurret = CreateDefaultSubobject<UStaticMeshComponent>("TankTurret");
	TankBarrel = CreateDefaultSubobject<UStaticMeshComponent>("TankBarrel");
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	AzimuthGimbal = CreateDefaultSubobject<USceneComponent>("AzimuthGimbal");
	TheCamera = CreateDefaultSubobject<UCameraComponent>("Camera");

	// Find the meshes we are going to use in our content folder
	auto TankBodyAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Game/Tank/tank_fbx_Body.tank_fbx_Body"));
	auto TankTrackAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Game/Tank/tank_fbx_Track.tank_fbx_Track"));
	auto TankTurretAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Game/Tank/tank_fbx_Turret.tank_fbx_Turret"));
	auto TankBarrelAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Game/Tank/tank_fbx_Barrel.tank_fbx_Barrel"));

	// Set the meshes to our static meshes
	if (TankBodyAsset.Object) TankBody->SetStaticMesh(TankBodyAsset.Object);
	if (TankTrackAsset.Object)
	{
		TankLeftTrack->SetStaticMesh(TankTrackAsset.Object);
		TankRightTrack->SetStaticMesh(TankTrackAsset.Object);
	}
	if (TankTurretAsset.Object) TankTurret->SetStaticMesh(TankTurretAsset.Object);
	if (TankBarrelAsset.Object) TankBarrel->SetStaticMesh(TankBarrelAsset.Object);

	// Put in appropriate heirarchy and attach sockets
	RootComponent = TankBody;
	TankTurret->SetupAttachment(TankBody, FName(TEXT("Turret")));
	TankBarrel->SetupAttachment(TankTurret, FName(TEXT("Barrel")));
	TankLeftTrack->SetupAttachment(TankBody, FName(TEXT("Left Track")));
	TankRightTrack->SetupAttachment(TankBody, FName(TEXT("Right Track")));
	AzimuthGimbal->SetupAttachment(TankBody);
	SpringArm->SetupAttachment(AzimuthGimbal);
	TheCamera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	// Put in proper positions and set parameters
	TankBody->SetSimulatePhysics(true);
	TankBody->SetMassOverrideInKg(NAME_None, 40000.0f, true);
	AzimuthGimbal->SetRelativeLocation(FVector(0.0f, 0.0f, 150.0f));
	SpringArm->TargetArmLength = 1000.0f;
	SpringArm->SetRelativeRotation(FRotator(-20.0f, 0.0f, 0.0f));
	SpringArm->TargetOffset = FVector(0.0f, 0.0f, 60.0f);
	SpringArm->bInheritRoll = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);
	// Camera movement
	PlayerInputComponent->BindAxis("AimAzimuth", this, &ATank::AzimuthTurn);
	PlayerInputComponent->BindAxis("AimElevation", this, &ATank::LookUp);
}

void ATank::AzimuthTurn(float Rate)
{
	AzimuthGimbal->AddLocalRotation(FRotator(0.0f, Rate, 0.0f));
}

void ATank::LookUp(float Rate)
{
	SpringArm->AddLocalRotation(FRotator(Rate, 0.0f, 0.0f));
}

