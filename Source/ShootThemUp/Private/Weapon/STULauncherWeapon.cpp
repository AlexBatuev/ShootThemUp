// Shoot Them Up Game. All Rights Reserved.

#include "Weapon/STULauncherWeapon.h"

#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Weapon/STUProjectile.h"

void ASTULauncherWeapon::StartFire()
{
    MakeShot();
}

void ASTULauncherWeapon::MakeShot()
{
    if (!GetWorld())
        return;

    if (IsAmmoEmpty())
    {
        UGameplayStatics::SpawnSoundAtLocation(GetWorld(), NoAmmoSound, GetActorLocation());
        return;
    }

    FVector TraceStart;
    FVector TraceEnd;
    if (!GetTraceData(TraceStart, TraceEnd))
        return;

    FHitResult HitResult;
    MakeHit(HitResult, TraceStart, TraceEnd);

    const auto EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
    const auto Direction = (EndPoint - GetMuzzleWorldLocation()).GetSafeNormal();
    const auto SpawnTransform = FTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
    auto Projectile = GetWorld()->SpawnActorDeferred<ASTUProjectile>(ProjectileClass, SpawnTransform);
    if (Projectile)
    {
        Projectile->SetShotDirection(Direction);
        Projectile->SetOwner(GetOwner());
        Projectile->FinishSpawning(SpawnTransform);
    }
    DecreaseAmmo();
    SpawnMuzzleFX();
    UGameplayStatics::SpawnSoundAttached(FireSound, WeaponMesh, MuzzleSocketName);
}
