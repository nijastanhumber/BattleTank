// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create the static meshes
	TankBody = CreateDefaultSubobject<UStaticMeshComponent>("TankBody");
	TankLeftTrack = CreateDefaultSubobject<UTankTrack>("TankLeftTrack");
	TankRightTrack = CreateDefaultSubobject<UTankTrack>("TankRightTrack");
	TankTurret = CreateDefaultSubobject<UTankTurret>("TankTurret");
	TankBarrel = CreateDefaultSubobject<UTankBarrel>("TankBarrel");

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	AzimuthGimbal = CreateDefaultSubobject<USceneComponent>("AzimuthGimbal");
	TheCamera = CreateDefaultSubobject<UCameraComponent>("Camera");

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>("Aiming Component");
	TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>("Movement Componenet");

	// Find the meshes we are going to use in our content folder
	//auto TankBodyAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Tank/tank_fbx_Body.tank_fbx_Body'"));
	//auto TankTrackAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Tank/tank_fbx_Track.tank_fbx_Track'"));
	//auto TankTurretAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Tank/tank_fbx_Turret.tank_fbx_Turret'"));
	//auto TankBarrelAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Tank/tank_fbx_Barrel.tank_fbx_Barrel'"));

	// Set the meshes to our static meshes
	//if (TankBodyAsset.Object) TankBody->SetStaticMesh(TankBodyAsset.Object);
	//if (TankTrackAsset.Object)
	//{
	//	TankLeftTrack->SetStaticMesh(TankTrackAsset.Object);
	//	TankRightTrack->SetStaticMesh(TankTrackAsset.Object);
	//}
	//if (TankTurretAsset.Object) TankTurret->SetStaticMesh(TankTurretAsset.Object);
	//if (TankBarrelAsset.Object) TankBarrel->SetStaticMesh(TankBarrelAsset.Object);

		

	// Put in appropriate heirarchy and attach sockets
	RootComponent = TankBody;
	TankTurret->SetupAttachment(TankBody, FName(TEXT("Turret")));
	TankBarrel->SetupAttachment(TankTurret, FName(TEXT("Barrel")));

	TankLeftTrack->SetupAttachment(RootComponent);
	TankRightTrack->SetupAttachment(RootComponent);
	TankLeftTrack->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), FName("LeftTrack"));
	TankRightTrack->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), FName("RightTrack"));
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
	TankBody->SetEnableGravity(true);
	TankLeftTrack->SetEnableGravity(false);
	TankRightTrack->SetEnableGravity(false);
	TankTurret->SetEnableGravity(false);
	TankBarrel->SetEnableGravity(false);

	TankAimingComponent->Initialize(TankBarrel, TankTurret);
	TankMovementComponent->Initialize(TankLeftTrack, TankRightTrack);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);
	// Movement
	PlayerInputComponent->BindAxis("AimAzimuth", this, &ATank::AzimuthTurn);
	PlayerInputComponent->BindAxis("AimElevation", this, &ATank::LookUp);
	PlayerInputComponent->BindAxis("MoveForward", this, &ATank::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATank::MoveRight);

	// Fire projectile
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ATank::Fire);
}

void ATank::AzimuthTurn(float Rate)
{
	AzimuthGimbal->AddLocalRotation(FRotator(0.0f, Rate, 0.0f));
}

void ATank::LookUp(float Rate)
{
	SpringArm->AddLocalRotation(FRotator(Rate, 0.0f, 0.0f));
}

void ATank::MoveForward(float Value)
{
	TankMovementComponent->IntendMoveForward(Value);
}

void ATank::MoveRight(float Value)
{
	TankMovementComponent->IntendMoveRight(Value);
}

void ATank::AimAt(FVector HitLocation)
{
	if (!ensure(TankAimingComponent)) { return; }
	TankAimingComponent->AimAt(HitLocation);
}

void ATank::Fire()
{
	TankAimingComponent->Fire();
}
