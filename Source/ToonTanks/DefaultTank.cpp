// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultTank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

ADefaultTank::ADefaultTank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(TurretMesh);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void ADefaultTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Movement
    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ADefaultTank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ADefaultTank::Turn);

	//Firing
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ADefaultTank::Fire);

	//Ammo Selection
	PlayerInputComponent->BindAction(TEXT("AmmoOne"), IE_Pressed, this, &ADefaultTank::AmmoOne);
	PlayerInputComponent->BindAction(TEXT("AmmoTwo"), IE_Pressed, this, &ADefaultTank::AmmoTwo);

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

		DrawDebugSphere(GetWorld(),
		HitResult.ImpactPoint,
		25.f,
		12,
		FColor::Red,
		false,
		-1.f);

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
}

void ADefaultTank::Move(float Value)
{
    FVector DeltaLocation = FVector::ZeroVector;
	DeltaLocation.X = Value * Speed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalOffset(DeltaLocation, true);
}

void ADefaultTank::Turn(float Value)
{
	FRotator DeltaRotation = FRotator::ZeroRotator;
	DeltaRotation.Yaw = Value * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalRotation(DeltaRotation, true);
}

void ADefaultTank::AmmoOne()
{
	if(selectedAmmo == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Already Selected!"));
		return;
	}
	selectedAmmo = 0;
	UE_LOG(LogTemp, Display, TEXT("Selected 0"));
}

void ADefaultTank::AmmoTwo()
{
	if(selectedAmmo == 1)
	{
		UE_LOG(LogTemp, Warning, TEXT("Already Selected!"));
		return;
	}
	selectedAmmo = 1;
	UE_LOG(LogTemp, Display, TEXT("Selected 1"));
}

void ADefaultTank::ReturnSelectedAmmo(int ammoType)
{
	ammoType = selectedAmmo;
}
