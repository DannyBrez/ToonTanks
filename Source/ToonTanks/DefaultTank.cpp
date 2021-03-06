// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultTank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

ADefaultTank::ADefaultTank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void ADefaultTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Movement
    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ADefaultTank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ADefaultTank::Turn);

	//Firing handled in blueprint
}

void ADefaultTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TankPlayerController)
	{
		FHitResult HitResult;
		TankPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, 
		false,
		HitResult);

		RotateTurret(HitResult.ImpactPoint);

	}
}

//Handles Tank death
void ADefaultTank::HandleDestruction()
{
    Super::HandleDestruction();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	//For later
    //Destroy();
	bAlive = false;
}

// Called when the game starts or when spawned
void ADefaultTank::BeginPlay()
{
	Super::BeginPlay();

	TankPlayerController = Cast<APlayerController>(GetController());

	//Set Tanks Default Values
	AmmoRemaining = MaxAmmo;
	CurrentSpeed = NormalSpeed;
	
}

void ADefaultTank::Move(float Value)
{
    FVector DeltaLocation = FVector::ZeroVector;
	DeltaLocation.X = Value * CurrentSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalOffset(DeltaLocation, true);
}

void ADefaultTank::Turn(float Value)
{
	FRotator DeltaRotation = FRotator::ZeroRotator;
	DeltaRotation.Yaw = Value * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalRotation(DeltaRotation, true);
}
