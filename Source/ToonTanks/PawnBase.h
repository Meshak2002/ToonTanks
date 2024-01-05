// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnBase.generated.h"

UCLASS()
class TOONTANKS_API APawnBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APawnBase();
	void DestructionHandler();
	void Fire();

protected:
	void LookTarget(FVector target,float speed);

private:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Collider",meta=(AllowPrivateAccess=true))
	class UCapsuleComponent* capCol;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = true))
		UStaticMeshComponent* base;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = true))
		UStaticMeshComponent* turret;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SpawnAt", meta = (AllowPrivateAccess = true))
		USceneComponent* SpawnPoint;
	UPROPERTY(EditAnywhere, Category="VFX")
		class UParticleSystem* deadEffect;
	
	// Called to bind functionality to input
	UPROPERTY(EditDefaultsOnly, Category="Spawn")
		TSubclassOf<class AProjectile> projectile;

	UPROPERTY(EditAnywhere, Category = "Audio")
		class USoundBase* audDestroy;


};
