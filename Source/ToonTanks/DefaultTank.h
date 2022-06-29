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
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Combat", meta =  (AllowPrivateAccess = "true"));
	int AmmoRemaining = 50;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat", meta =  (AllowPrivateAccess = "true"));
	int MaxAmmo = 50;

	//Blueprint variable --- Sets the current ammo based on Projectile ammo cost.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Combat", meta =  (AllowPrivateAccess = "true"));
	int CurrentAmmoCost = 1;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components", meta = (AllowPrivateAccess = "true"));
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components", meta = (AllowPrivateAccess = "true"));
	class UCameraComponent* Camera;

	//Tank Speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement",  meta = (AllowPrivateAccess = "true"));
	float NormalSpeed = 200.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Movement",  meta = (AllowPrivateAccess = "true"));
	float CurrentSpeed = 200.f;

	//Tank Turnrate
	UPROPERTY(EditAnywhere, Category="Movement");
	float TurnRate = 100.f;

	//Moving functions
	void Move(float Value);
	void Turn(float Value);

	// ------------------------------ Blueprint variable ------------------------------ //

	//Fire Rate variables
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float CurrentFireRate = 1.f;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bCanFire = true;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bIsTriggerPressed = true;

	//Overheat Mechanic
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float Overheat = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Overheat Ability", meta = (AllowPrivateAccess = "true"))
	float MaxOverheat = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Overheat Ability", meta = (AllowPrivateAccess = "true"))
	float SpeedUpSpeed = 400.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Overheat Ability", meta = (AllowPrivateAccess = "true"))
	float OverheatedSpeed = 150.f;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bOverheated = false;
	
	APlayerController* TankPlayerController;
	
};
