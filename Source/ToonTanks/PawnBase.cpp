// Fill out your copyright notice in the Description page of Project Settings.
#include "PawnBase.h"
#include "Public/Projectile.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APawnBase::APawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	capCol = CreateDefaultSubobject<UCapsuleComponent>("Capsule Collider");
	RootComponent = capCol;

	base = CreateDefaultSubobject<UStaticMeshComponent>("Base Tank");
	base->SetupAttachment(capCol); 

	turret = CreateDefaultSubobject<UStaticMeshComponent>("Turret");
	turret->SetupAttachment(base);

	SpawnPoint = CreateDefaultSubobject<USceneComponent>("SpawnPoint");
	SpawnPoint->SetupAttachment(turret);
}

void APawnBase::DestructionHandler() {
	//Music and SFX OFF
	if (audDestroy)
			UGameplayStatics::PlaySoundAtLocation(this, audDestroy, GetActorLocation());
	if(deadEffect)
		UGameplayStatics::SpawnEmitterAtLocation(this, deadEffect, GetActorLocation(),GetActorRotation());
}

void APawnBase::LookTarget(FVector target,float speed) {
	FVector dist = target - turret->GetComponentLocation();
	FRotator rotTowards = FRotator(0,dist.Rotation().Yaw,0);
	turret->SetWorldRotation(FMath::RInterpTo(turret->GetComponentRotation(), rotTowards, UGameplayStatics::GetWorldDeltaSeconds(this), speed));
}

void APawnBase::Fire() {
	//DrawDebugSphere(GetWorld(), SpawnPoint->GetComponentLocation(), 20, 8, FColor::Red, false, 2);
	auto projectil = GetWorld()->SpawnActor<AProjectile>(projectile, SpawnPoint->GetComponentLocation(), SpawnPoint->GetComponentRotation());
	projectil->SetOwner(this);
}



// Called to bind functionality to input

















