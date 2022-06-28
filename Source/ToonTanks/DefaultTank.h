// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "DefaultTank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ADefaultTank : public ABasePawn
{
	GENERATED_BODY()

public:

	// Sets default values for this pawn's properties
	ADefaultTank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

	APlayerController* GetTankPlayerController() const { return TankPlayerController; }

	bool bAlive = true;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Blueprint variable --- Sets the remaining ammo
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat", meta =  (AllowPrivateAccess = "true"));
	int AmmoRemaining = 50;

	//Blueprint variable --- Sets the current ammo based on Projectile ammo cost.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat", meta =  (AllowPrivateAccess = "true"));
	int CurrentAmmoCost = 1;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components", meta = (AllowPrivateAccess = "true"));
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components", meta = (AllowPrivateAccess = "true"));
	class UCameraComponent* Camera;

	//Tank Speed
	UPROPERTY(EditAnywhere, Category="Movement");
	float Speed = 200.f;

	//Tank Turnrate
	UPROPERTY(EditAnywhere, Category="Movement");
	float TurnRate = 100.f;

	//Fire Rate
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float CurrentFireRate = 1.f;
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bCanFire = true;
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bIsTriggerPressed = true;

	void Move(float Value);
	void Turn(float Value);

	APlayerController* TankPlayerController;
	
};
