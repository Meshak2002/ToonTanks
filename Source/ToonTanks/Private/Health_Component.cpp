// Fill out your copyright notice in the Description page of Project Settings.

#include "Health_Component.h"
#include "GameMode_.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealth_Component::UHealth_Component()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}

// Called when the game starts
void UHealth_Component::BeginPlay()
{
	Super::BeginPlay();
	Health = MaxHealth;
	gameMode = Cast<AGameMode_>(UGameplayStatics::GetGameMode(this));
	// ...
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealth_Component::DamageTaken);
}

// Called every frame
void UHealth_Component::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealth_Component::DamageTaken(AActor* damagedActor, float damageAmount, const UDamageType* damageType, class AController* Instigator, AActor* damager) {
	UE_LOG(LogTemp, Warning, TEXT("Duck"));
	if (Health > damageAmount) {
		Health -= damageAmount;
		UE_LOG(LogTemp, Warning, TEXT("Health On :%f"), Health);
	}
	else {
		if(gameMode)
			gameMode->DiedActor(damagedActor);
		return;
	}
	
	
}

