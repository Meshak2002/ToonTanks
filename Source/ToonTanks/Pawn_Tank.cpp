#include "Pawn_Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

APawn_Tank::APawn_Tank() {
    PrimaryActorTick.bCanEverTick = true;
    springArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
    springArm->SetupAttachment(RootComponent);
    cameraComp = CreateDefaultSubobject<UCameraComponent>("Camera");
    cameraComp->SetupAttachment(springArm);
}

void APawn_Tank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis("MoveForward", this, &APawn_Tank::Move);
    PlayerInputComponent->BindAxis("Turn", this, &APawn_Tank::Turn);
    PlayerInputComponent->BindAction("Fire",IE_Pressed, this, &APawn_Tank::Fire);
}

// Called every frame
void APawn_Tank::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (playerController) {
        FHitResult hit;
        playerController->GetHitResultUnderCursor(ECC_Visibility, false, hit);
       // DrawDebugSphere(GetWorld(), hit.ImpactPoint, 25, 12, FColor::Blue);
        LookTarget(hit.ImpactPoint, TurretRotSpeed);
    }
}

void APawn_Tank::Fire() {
    Super::Fire();
    GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(ProjCamShake);
}

void APawn_Tank::BeginPlay()
{
    Super::BeginPlay();
    playerController = Cast<APlayerController>(GetController());
}
void APawn_Tank::DestructionHandler() {
    Super::DestructionHandler();
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
    ALive = false;
    if (DesCamShake)
        GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DesCamShake);
}

void APawn_Tank::Move(float x) {
    FVector offset(0.f);
    offset.X = x;
    float deltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
    AddActorLocalOffset(offset*speed* deltaTime,true);
}
void APawn_Tank::Turn(float x) {
    FRotator rotate = FRotator::ZeroRotator;
    rotate.Yaw = TurnRate * x * UGameplayStatics::GetWorldDeltaSeconds(this);
    AddActorLocalRotation(rotate, true);
}
