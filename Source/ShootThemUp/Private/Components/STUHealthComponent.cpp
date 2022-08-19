// Shoot Them Up Game. All Rights Reserved.

#include "Components/STUHealthComponent.h"

#include "STUGameModeBase.h"
#include "GameFramework/Character.h"
#include "GameFramework/GameState.h"
#include "Perception/AISense_Damage.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All);

// Sets default values for this component's properties
USTUHealthComponent::USTUHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = NAME_FALSE;
}

bool USTUHealthComponent::TryToAddHealth(const float HealthCount)
{
    if (IsDead() || IsHealthFull())
        return false;

    SetHealth(Health + HealthCount);
    UE_LOG(LogHealthComponent, Warning, TEXT("Health were added"));

    return true;
}

// Called when the game starts
void USTUHealthComponent::BeginPlay()
{
    Super::BeginPlay();

    check(MaxHealth > 0);

    SetHealth(MaxHealth);

    const auto Owner = GetOwner();
    if (Owner)
    {
        Owner->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeAnyDamage);
        Owner->OnTakePointDamage.AddDynamic(this, &USTUHealthComponent::OnTakePointDamage);
        Owner->OnTakeRadialDamage.AddDynamic(this, &USTUHealthComponent::OnTakeRadialDamage);
    }
}

void USTUHealthComponent::OnTakeAnyDamage(
    AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
    UE_LOG(LogHealthComponent, Display, TEXT("On any damage: %f"), Damage);
}

void USTUHealthComponent::OnTakePointDamage(AActor* DamagedActor, float Damage, AController* InstigatedBy, FVector HitLocation,
    UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const UDamageType* DamageType, AActor* DamageCauser)
{
    const auto FinalDamage = Damage * GetPointDamageModifier(DamagedActor, BoneName);
    UE_LOG(LogHealthComponent, Display, TEXT("On point damage: %f, final damage: %f, bone: %s"), Damage, FinalDamage, *BoneName.ToString());
    ApplyDamage(FinalDamage, InstigatedBy);
}

void USTUHealthComponent::OnTakeRadialDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, FVector Origin,
    FHitResult HitInfo, AController* InstigatedBy, AActor* DamageCauser)
{
    UE_LOG(LogHealthComponent, Display, TEXT("On radial damage: %f"), Damage);
    ApplyDamage(Damage, InstigatedBy);
}

void USTUHealthComponent::OnHeal()
{
    if (IsDead())
        return;

    SetHealth(Health + HealModifier);

    if (IsHealthFull() && GetWorld())
    {
        GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
    }
}

void USTUHealthComponent::SetHealth(const float Value)
{
    const auto NewHealth = FMath::Clamp(Value, 0.f, MaxHealth);
    const auto HealthDelta = NewHealth - Health;
    Health = NewHealth;
    OnHealthChanged.Broadcast(Health, HealthDelta);
}

bool USTUHealthComponent::IsHealthFull() const
{
    return FMath::IsNearlyEqual(Health, MaxHealth);
}

void USTUHealthComponent::PlayCameraShake() const
{
    if (IsDead()) return;
    
    const auto Player = Cast<APawn>(GetOwner());
    if (!Player) return;
    
    const auto Controller = Player->GetController<APlayerController>();
    if(!Controller || !Controller->PlayerCameraManager) return;
    
    Controller->PlayerCameraManager->StartCameraShake(CameraShake);
}

void USTUHealthComponent::OnKilled(const AController* KillerController) const
{
    if (!GetWorld()) return;
    
    const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
    if (!GameMode) return;

    const auto Player = Cast<APawn>(GetOwner());
    const auto VictimController = Player ? Player->Controller : nullptr;
    
    GameMode->OnKill(KillerController, VictimController);
}

void USTUHealthComponent::ApplyDamage(float Damage, AController* InstigatedBy)
{
    if (Damage <= 0.0f || IsDead())
        return;

    SetHealth(Health - Damage);
    GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
    
    if (IsDead())
    {
        OnKilled(InstigatedBy);
        OnDeath.Broadcast();
    }
    else if (AutoHeal && GetWorld() && !GetWorld()->GetTimerManager().IsTimerActive(HealTimerHandle))
    {
        GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &USTUHealthComponent::OnHeal, HealUpdateTime,
            true, HealDelay);
    }

    PlayCameraShake();
    ReportDamageEvent(Damage, InstigatedBy);
}

float USTUHealthComponent::GetPointDamageModifier(AActor* DamagedActor, const FName& BoneName)
{
    const auto Character = Cast<ACharacter>(DamagedActor);
    if (!Character || !Character->GetMesh() || !Character->GetMesh()->GetBodyInstance(BoneName)) return 1.f;

    const auto PhysMat = Character->GetMesh()->GetBodyInstance(BoneName)->GetSimplePhysicalMaterial();
    if(!PhysMat || !DamageModifiers.Contains(PhysMat)) return 1.f;

    return DamageModifiers[PhysMat];
}

void USTUHealthComponent::ReportDamageEvent(float Damage, AController* InstigatedBy)
{
    if(!InstigatedBy || !InstigatedBy->GetPawn() || !GetOwner()) return;
    
    UAISense_Damage::ReportDamageEvent(GetWorld(), GetOwner(), InstigatedBy->GetPawn(), Damage,
        InstigatedBy->GetPawn()->GetActorLocation(), GetOwner()->GetActorLocation());
}
