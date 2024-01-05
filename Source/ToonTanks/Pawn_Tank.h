// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "Pawn_Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API APawn_Tank : public APawnBase
{
	GENERATED_BODY()
public :
	 APawn_Tank();
	 virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	 void Move(float x);
	 void Turn(float x);
	 virtual void Tick(float DeltaTime) override;
	 void DestructionHandler();  
	 APlayerController* GetPlayerController() const {
		 return playerController;
	 }
	 UPROPERTY()
		 bool ALive = true;

private:
	void Fire();
	UPROPERTY(EditAnywhere)
		float speed;
	UPROPERTY(EditAnywhere)
		float TurnRate;
	UPROPERTY(EditAnywhere)
		float TurretRotSpeed;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = true))
		class USpringArmComponent* springArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = true))
		class UCameraComponent* cameraComp; 
	APlayerController* playerController;
	UPROPERTY(EditAnywhere,Category="Camera Shake")
		TSubclassOf<UCameraShakeBase> DesCamShake;
	UPROPERTY(EditAnywhere, Category = "Camera Shake")
		TSubclassOf<UCameraShakeBase> ProjCamShake;
};
