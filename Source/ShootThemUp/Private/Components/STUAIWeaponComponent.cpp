// Shoot Them Up Game. All Rights Reserved.


#include "Components/STUAIWeaponComponent.h"

void USTUAIWeaponComponent::StartFire()
{
    //Super::StartFire();

    if (!CanFire()) return;

    if(CurrentWeapon->IsAmmoEmpty())
    {
        NextWeapon();
    }
    else
    {
        CurrentWeapon->StartFire();
    }
}

void USTUAIWeaponComponent::NextWeapon()
{
    //Super::NextWeapon();

    if (!CanEquip()) return;

    auto NextIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
    while(NextIndex != CurrentWeaponIndex)
    {
        if(!Weapons[NextIndex]->IsAmmoEmpty()) break;
        NextIndex = (NextIndex + 1) % Weapons.Num();
    }

    if (CurrentWeaponIndex != NextIndex)
    {
        CurrentWeaponIndex = NextIndex;
        EquipWeapon(CurrentWeaponIndex);
    }
}
