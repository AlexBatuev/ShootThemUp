// Shoot Them Up Game. All Rights Reserved.

#include "Pickups/STUBasePickup.h"

#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

DEFINE_LOG_CATEGORY_STATIC(LogBasePickup, All, All);

ASTUBasePickup::ASTUBasePickup()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    CollisionComponent->InitSphereRadius(50.f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
    SetRootComponent(CollisionComponent);
}

void ASTUBasePickup::BeginPlay()
{
	Super::BeginPlay();

    check(CollisionComponent);

    UpdateYawRotation();
}

void ASTUBasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    AddActorLocalRotation(FRotator(0.f, YawRotation, 0.f));
}

bool ASTUBasePickup::CouldBeTaken() const
{
    return !GetWorldTimerManager().IsTimerActive(RespawnTimerHandle);
}

void ASTUBasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    const auto Pawn = Cast<APawn>(OtherActor);
    if (GivePickupTo(Pawn))
    {
        PickupWasTaken();
    }
}

void ASTUBasePickup::UpdateYawRotation() {
    const auto Direction = FMath::RandBool() ? 1 : -1;
    YawRotation = FMath::RandRange(1.f, 2.f) * Direction;
}

void ASTUBasePickup::PickupWasTaken()
{
    CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
    if (GetRootComponent())
    {
        GetRootComponent()->SetVisibility(false, true);
    }

    UGameplayStatics::PlaySoundAtLocation(GetWorld(), TakeSound, GetActorLocation());
    GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ASTUBasePickup::Respawn, RespawnTime);
}

void ASTUBasePickup::Respawn()
{
    UpdateYawRotation();
    CollisionComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
    if (GetRootComponent())
    {
        GetRootComponent()->SetVisibility(true, true);
    }
}

bool ASTUBasePickup::GivePickupTo(APawn* PlayerPawn)
{
    return false;
}

