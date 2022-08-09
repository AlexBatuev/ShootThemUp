// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "Weapon/STUBaseWeapon.h"
#include "STUAmmoPercentDecorator.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUAmmoPercentDecorator : public UBTDecorator
{
	GENERATED_BODY()

public:
    USTUAmmoPercentDecorator();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
    TSubclassOf<ASTUBaseWeapon> WeaponType;
    
    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
