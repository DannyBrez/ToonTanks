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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components", meta = (AllowPrivateAccess = "true"));
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components", meta = (AllowPrivateAccess = "true"));
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category="Movement");
	float Speed = 200.f;
	UPROPERTY(EditAnywhere, Category="Movement");
	float TurnRate = 100.f;

	void Move(float Value);
	void Turn(float Value);

	APlayerController* TankPlayerController;
	
};