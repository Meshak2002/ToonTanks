// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameMode_.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AGameMode_ : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	void DiedActor(AActor* actor);
	void startTime();
	UFUNCTION(BlueprintImplementableEvent)
		void startCanvas();

	UFUNCTION(BlueprintImplementableEvent)
		void GameOver(bool state);
	int32 GetTowersCount();
private :
	class APawn_Tank* tank;
	class ATankPlayerController* tankController;

	int32 totTowers;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
