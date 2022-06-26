// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	void HandleDestruction();

protected:

	void RotateTurret(FVector LookAtTarget);
	UFUNCTION(BlueprintCallable)
	void Fire();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components", meta =  (AllowPrivateAccess = "true"));
	UStaticMeshComponent* TurretMesh;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components", meta = (AllowPrivateAccess = "true"));
	class UCapsuleComponent* CapsuleComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components", meta = (AllowPrivateAccess = "true"));
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components", meta = (AllowPrivateAccess = "true"));
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"));
	TSubclassOf<class ADefaultProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Combat");
	UParticleSystem* DeathParticles;

	UPROPERTY(EditAnywhere, Category = "Combat");
	class USoundBase* DeathSound;

	UPROPERTY(EditAnywhere, Category = "Combat");
	TSubclassOf<class UCameraShakeBase> DeathCameraShakeClass;
};
