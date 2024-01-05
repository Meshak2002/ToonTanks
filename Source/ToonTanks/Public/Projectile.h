// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

private :
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = true))
		UStaticMeshComponent* Projectile;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
		class UProjectileMovementComponent* projMovement;

	UFUNCTION()
		void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere,Category="VFX")
		class UParticleSystem* particleEffect;

	UPROPERTY(VisibleAnywhere, Category = "VFX")
		class UParticleSystemComponent* particleFlow;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UCameraShakeBase> projCamShake;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, Category = "Audio")
		class USoundBase* ProjFlo;
	UPROPERTY(EditAnywhere, Category = "Audio")
		class USoundBase* ProjHit;
};
