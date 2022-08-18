// Shoot Them Up Game. All Rights Reserved.


#include "Weapon/Components/STUWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Sound/SoundCue.h"

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
    auto ImpactData = DefaultImpactData;

	if (HitResult.PhysMaterial.IsValid())
	{
        const auto Material = HitResult.PhysMaterial.Get();
        if (ImpactDataMap.Contains(Material))
        {
            ImpactData = ImpactDataMap[Material];
        }
	}

    UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactData.Sound, HitResult.ImpactPoint);
 
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(
        GetWorld(), ImpactData.UNiagaraEffect, HitResult.ImpactPoint, HitResult.ImpactPoint.Rotation());

    const auto DecalComponent = UGameplayStatics::SpawnDecalAtLocation(
        GetWorld(), ImpactData.DecalData.Material, ImpactData.DecalData.Size, HitResult.ImpactPoint, HitResult.ImpactNormal.Rotation());
 
    if (DecalComponent)
    {
        DecalComponent->SetFadeOut(ImpactData.DecalData.LifeTime, ImpactData.DecalData.FadeOutTime);
    }
}

