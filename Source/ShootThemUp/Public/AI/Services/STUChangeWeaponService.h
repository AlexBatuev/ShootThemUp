// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "STUChangeWeaponService.generated.h"

UCLASS()
class SHOOTTHEMUP_API USTUChangeWeaponService : public UBTService
{
	GENERATED_BODY()

public:
    USTUChangeWeaponService();
    
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI", meta = (ClampMin = 0.f, ClampMax = 1.f))
    float Probability = 0.5f;

    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};