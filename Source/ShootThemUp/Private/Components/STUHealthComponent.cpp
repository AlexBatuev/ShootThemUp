// Shoot Them Up Game. All Rights Reserved.

#include "Components/STUHealthComponent.h"

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
    }
}

void USTUHealthComponent::OnTakeAnyDamage(
    AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
    if (Damage <= 0.0f || IsDead())
        return;

    SetHealth(Health - Damage);

    if (IsDead())
    {
        GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
        OnDeath.Broadcast();
    }
    else if (AutoHeal && GetWorld() && !GetWorld()->GetTimerManager().IsTimerActive(HealTimerHandle))
    {
        GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &USTUHealthComponent::OnHeal, HealUpdateTime, true, HealDelay);
    }
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
    Health = FMath::Clamp(Value, 0.f, MaxHealth);
    OnHealthChanged.Broadcast(Health);
}

bool USTUHealthComponent::IsHealthFull() const
{
    return FMath::IsNearlyEqual(Health, MaxHealth);
}
