// Shoot Them Up Game. All Rights Reserved.


#include "Weapon/Components/STUWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

USTUWeaponFXComponent::USTUWeaponFXComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USTUWeaponFXComponent::BeginPlay()
{
	Super::BeginPlay();
}

void USTUWeaponFXComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USTUWeaponFXComponent::PlayImpactFX(const FHitResult& HitResult)
{
    auto Effect = DefaultImpactData;

	if (HitResult.PhysMaterial.IsValid())
	{
        const auto Material = HitResult.PhysMaterial.Get();
        if (ImpactDataMap.Contains(Material))
        {
            Effect = ImpactDataMap[Material];
        }
	}
 
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(
        GetWorld(), Effect.UNiagaraEffect, HitResult.ImpactPoint, HitResult.ImpactPoint.Rotation());

    const auto DecalComponent = UGameplayStatics::SpawnDecalAtLocation(
        GetWorld(), Effect.DecalData.Material, Effect.DecalData.Size, HitResult.ImpactPoint, HitResult.ImpactNormal.Rotation());
 
    if (DecalComponent)
    {
        DecalComponent->SetFadeOut(Effect.DecalData.LifeTime, Effect.DecalData.FadeOutTime);
    }
}

