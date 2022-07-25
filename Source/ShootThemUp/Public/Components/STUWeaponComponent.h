// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "STUCoreTypes.h"
#include "Components/ActorComponent.h"
#include "Weapon/STUBaseWeapon.h"
#include "STUWeaponComponent.generated.h"

class ASTUBaseWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTUWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USTUWeaponComponent();

    void StartFire();
    void StopFire();
    void NextWeapon();
    void Reload();
    bool GetCurrentWeaponUIData(FWeaponUIData& UIData) const;
    bool GetCurrentAmmoData(FAmmoData& AmmoData) const;
    bool TryToAddAmmo(TSubclassOf<ASTUBaseWeapon> WeaponType, int32 ClipsCount);

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TArray<FWeaponData> WeaponData;

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponEquipSocketName = "WeaponSocket";

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponArmorySocketName = "ArmorySocket";

    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    UAnimMontage* EquipAnimMontage = nullptr;

	virtual void BeginPlay() override;
    virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

private:
    UPROPERTY()
    ASTUBaseWeapon* CurrentWeapon = nullptr;

    UPROPERTY()
    TArray<ASTUBaseWeapon*> Weapons;

    UPROPERTY()
    UAnimMontage* CurrentReloadAnimMontage = nullptr;

    int32 CurrentWeaponIndex = 0;
    bool EquipAnimInProgress = false;
    bool ReloadAnimInProgress = false;

    void SpawnWeapons();
    void AttachWeaponToSocket(ASTUBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);
    void EquipWeapon(int32 WeaponIndex);

    void PlayAnimMontage(UAnimMontage* AnimMontage);
    void InitAnimations();
    void OnEquipFinished(USkeletalMeshComponent* MeshComponent);
    void OnReloadFinished(USkeletalMeshComponent* MeshComponent);

    bool CanFire();
    bool CanEquip();
    bool CanReload();

    void OnEmptyClip(ASTUBaseWeapon* EmptyWeapon);
    void ChangeClip();
};
