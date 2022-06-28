// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DefaultProjectile.generated.h"

class USoundBase;

UCLASS()
class TOONTANKS_API ADefaultProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADefaultProjectile();

	//Blueprint Variable --- Each TSubclassOf Projectile will have a different ammo cost
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat", meta =  (AllowPrivateAccess = "true"));
	int AmmoCost = 1;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Combat", meta = (AllowPrivateAccess = "true"));
	class UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Movement", meta = (AllowPrivateAccess = "true"));
	class UProjectileMovementComponent* ProjectileMovement;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	//Damage variables
	UPROPERTY(EditAnywhere, Category = "Combat")
	float Damage = 50.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float ExplodeDamage = 50.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float DamageRadius = 50.f;

	//Fire Rate
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRate = 1.f;

	//Visuals and Sound
	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystem* HitParticles;

	UPROPERTY(VisibleAnywhere, Category = "Combat")
	class UParticleSystemComponent* ParticleTrail;

	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase* LaunchSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class UCameraShakeBase> HitCameraShakeClass;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
