 // Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode_.h"
#include "Kismet/GameplayStatics.h"
#include "../Pawn_Tank.h" 
#include "../PawnTurret.h"
#include "TankPlayerController.h"
#include "../PawnTurret.h"

void AGameMode_::DiedActor(AActor* actor) {
	
		if (actor == tank) {
			tank->DestructionHandler();
			if (tankController) {
				tankController->setPlayerControllerState(false);
			}
			GameOver(false);
		}
		else if (APawnTurret* turret = Cast<APawnTurret>(actor)) {
			turret->DestructionHandler();
			--totTowers;
			if (totTowers == 0) {
				GameOver(true);
			}
	}
}
void AGameMode_::startTime() {
	if(tankController)
		tankController->setPlayerControllerState(false);
	FTimerHandle timeHandle;
	startCanvas();
	if (tankController) {
		FTimerDelegate timerDeleg = FTimerDelegate::CreateUObject(tankController, &ATankPlayerController::setPlayerControllerState, true);
		GetWorldTimerManager().SetTimer(timeHandle, timerDeleg, 3, false);
		
	}
}

void AGameMode_::BeginPlay()
{
	Super::BeginPlay();
	tank = Cast<APawn_Tank>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	tankController = Cast<ATankPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	totTowers = GetTowersCount();
	startTime();
}

int32 AGameMode_::GetTowersCount() {
	TArray<AActor*> turrets;
	UGameplayStatics::GetAllActorsOfClass(this, APawnTurret::StaticClass(), turrets);
	return turrets.Num();
}


