// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultTower.h"
#include "DefaultTank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"


void ADefaultTower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if(InFireRange())
    {
        RotateTurret(Tank->GetActorLocation());
    }
}

//Handles tower death
void ADefaultTower::HandleDestruction()
{
    Super::HandleDestruction();
    Destroy();
}


void ADefaultTower::BeginPlay()
{
    Super::BeginPlay();

    Tank = Cast<ADefaultTank>(UGameplayStatics::GetPlayerPawn(this, 0));

    GetWorldTimerManager().SetTimer(FireRateTimerHandle,
     this, 
     &ADefaultTower::CheckFireCondition,
     FireRate,
     true);
}

void ADefaultTower::CheckFireCondition()
{
    if(Tank == nullptr)
    {
        return;
    }
    if(InFireRange() && Tank->bAlive)
    {
        Fire();
    }
}

bool ADefaultTower::InFireRange()
{
    if(Tank)
    {
        float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
        if(Distance <= FireRange)
        {
            return true;
        }
    }
    return false;
}

