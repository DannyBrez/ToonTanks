// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "DefaultTank.h"
#include "DefaultTower.h"
#include "ToonTanksPlayerController.h"

void AToonTanksGameMode::ActorDied(AActor *DeadActor)
{
    //Tank Death
    if (DeadActor == Tank)
    {
        Tank->HandleDestruction();
        //Gets Player Controller to disable mouse and input
        if(ToonTanksPlayerController)
        {
            ToonTanksPlayerController->SetPlayerEnabledState(false);
        }
        //GameOver blueprint prints Loss.
        GameOver(false);
    }
    //Tower Death
    else if (ADefaultTower* DestroyedTower = Cast<ADefaultTower>(DeadActor))
    {
        DestroyedTower->HandleDestruction();
        TargetTowers--;
        if(TargetTowers == 0)
        {
            //GameOver blueprint prints Win.
            GameOver(true);
        }
    }
}

void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();

    HandleGameStart();

}

//Game Start Handler
void AToonTanksGameMode::HandleGameStart()
{
    //Sets TargetTowers 
    TargetTowers = GetTargetTowerCount();
    //Gets the Tank and Player Controller
    Tank = Cast<ADefaultTank>(UGameplayStatics::GetPlayerPawn(this, 0));
    ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

    //Start game blueprint begins
    StartGame();

    //Countdown Timer for level start
    if (ToonTanksPlayerController)
    {
        ToonTanksPlayerController->SetPlayerEnabledState(false);

        FTimerHandle PlayerEnableTimerHandle;

        FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(ToonTanksPlayerController, 
            &AToonTanksPlayerController::SetPlayerEnabledState, 
            true);

        GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, 
            PlayerEnableTimerDelegate, 
            StartDelay, 
            false);
    }
}
//Gets tower count in level
int32 AToonTanksGameMode::GetTargetTowerCount()
{
    TArray<AActor*> Towers;

    UGameplayStatics::GetAllActorsOfClass(this, ADefaultTower::StaticClass(), Towers);
    return Towers.Num();
}

