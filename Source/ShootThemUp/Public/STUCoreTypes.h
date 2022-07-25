#pragma once

#include "STUCoreTypes.generated.h"

// Weapon

class ASTUBaseWeapon;
DECLARE_MULTICAST_DELEGATE_OneParam(FOnClipEmptySignature, ASTUBaseWeapon*);

USTRUCT(BlueprintType)
struct FAmmoData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    int32 Bullets;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (EditCondition = "!Infinite"))
    int32 Clips;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    bool Infinite;
};

USTRUCT(BlueprintType)
struct FWeaponData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation")
    TSubclassOf<ASTUBaseWeapon> WeaponClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation")
    UAnimMontage* ReloadAnimMontage;
};

// Health

DECLARE_MULTICAST_DELEGATE(FOnDeathSignature);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float);

USTRUCT(BlueprintType)
struct FWeaponUIData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    UTexture2D* MainIcon;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    UTexture2D* CrossHairIcon;
};

