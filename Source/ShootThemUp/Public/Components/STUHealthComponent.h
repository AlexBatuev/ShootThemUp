// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "STUCoreTypes.h"
#include "Components/ActorComponent.h"
#include "STUHealthComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTUHealthComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    USTUHealthComponent();

    FOnDeathSignature OnDeath;
    FOnHealthChangedSignature OnHealthChanged;

    UFUNCTION(BlueprintCallable, Category = "Health")
    bool IsDead() const { return FMath::IsNearlyZero(Health); }

    float GetHealth() const { return Health; }

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Heal")
    bool AutoHeal = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = AutoHeal))
    float HealUpdateTime = 0.3f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = AutoHeal))
    float HealDelay = 3.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = AutoHeal))
    float HealModifier = 1.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = 0.f, ClampMax = 1000.f))
    float MaxHealth = 100.f;

    // Called when the game starts
    virtual void BeginPlay() override;

private:
    float Health = 0.f;

    FTimerHandle HealTimerHandle;

    UFUNCTION()
    void OnTakeAnyDamage(
        AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

    void OnHeal();

    void SetHealth(float Value);
};
