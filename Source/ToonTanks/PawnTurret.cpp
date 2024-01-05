// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h" 
#include "Pawn_Tank.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

APawnTurret::APawnTurret() {

}
void APawnTurret::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (TankCheckIn()) {
            LookTarget(tank->GetActorLocation(), 10);
             
    }
}

void APawnTurret::BeginPlay()
{
    Super::BeginPlay();
    tank = Cast<APawn_Tank>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
       // Cast<APawn_Tank>(GetWorld()->GetFirstPlayerController()->GetPawn());
    GetWorldTimerManager().SetTimer(timeHandler, this, &APawnTurret::FireAfterTime, fireRate, true);
}

void  APawnTurret::FireAfterTime() {
    if (TankCheckIn()) {
        Fire();
    }
}
void APawnTurret::DestructionHandler() {
    Super::DestructionHandler();
    Destroy();
}
bool APawnTurret::TankCheckIn() {
    if (tank && tank->ALive) {
        if (FVector::Dist(GetActorLocation(), tank->GetActorLocation()) < shootDist) {
            return true;
        }
    }
    return false;
}