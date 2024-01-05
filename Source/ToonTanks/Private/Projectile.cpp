// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Projectile = CreateDefaultSubobject<UStaticMeshComponent>("Projectile");
	RootComponent = Projectile; 
	projMovement = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile Movement");
	projMovement->InitialSpeed = 2000;
	projMovement->MaxSpeed = 3000;
	particleFlow = CreateDefaultSubobject<UParticleSystemComponent>("Particle Flow");
	particleFlow->SetupAttachment(Projectile);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	this->OnActorHit.AddDynamic(this, &AProjectile::OnHit);
	particleFlow->SetupAttachment(RootComponent);
	if (ProjFlo)
		UGameplayStatics::PlaySoundAtLocation(this, ProjFlo, GetActorLocation());
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit) {		
	
	if (GetOwner()) {
		auto instigator = GetOwner()->GetInstigatorController();
		if (instigator){
			if (OtherActor != GetOwner() && OtherActor != NULL && OtherActor != this) {
				UGameplayStatics::ApplyDamage(OtherActor, 25, instigator, this, UDamageType::StaticClass());
				UGameplayStatics::SpawnEmitterAtLocation(this, particleEffect, GetActorLocation(), GetActorRotation());
				if (ProjHit)
					UGameplayStatics::PlaySoundAtLocation(this, ProjHit, GetActorLocation());
				if (projCamShake && OtherActor== GetWorld()->GetFirstPlayerController()->GetPawn())
					GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(projCamShake);
				Destroy();
			}
		}
	}
	else {
		Destroy(); 
	}
}
