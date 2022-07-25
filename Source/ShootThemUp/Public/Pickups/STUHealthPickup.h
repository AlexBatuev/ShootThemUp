// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/STUBasePickup.h"
#include "STUHealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUHealthPickup : public ASTUBasePickup
{
	GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = 1.f, ClampMax = 100.f))
    float HealthCount = 100.f;

private:
    virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
