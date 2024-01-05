// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTurret.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API APawnTurret : public APawnBase
{
	GENERATED_BODY()
public:
	APawnTurret();
	virtual void Tick(float DeltaTime) override;
	void DestructionHandler();

private:
	UPROPERTY(EditAnywhere)
		float shootDist;
	UPROPERTY()
		class APawn_Tank* tank;

	UPROPERTY()
		FTimerHandle timeHandler;
	UPROPERTY(EditAnywhere)
		float fireRate=2;
	void FireAfterTime();

	bool TankCheckIn();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
