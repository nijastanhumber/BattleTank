// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class UParticleSystemComponent;
class UStaticMeshComponent;
class URadialForceComponent;

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent, Category = "Collision", meta = (AllowPrivateAccess = "true"))
		void OnHit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComponent, FVector NormalImpulse, const FHitResult &Hit);
	void OnHit_Implementation(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComponent, FVector NormalImpulse, const FHitResult &Hit);

	void OnTimerExpire();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UProjectileMovementComponent *ProjectileMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent *CollisionMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent *LaunchBlast;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent *ImpactBlast;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		URadialForceComponent *ExplosionForce;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float DestroyDelay = 10.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float ProjectileDamage = 20.0f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void LaunchProjectile(float Speed);
};
