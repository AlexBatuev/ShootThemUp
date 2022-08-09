// Shoot Them Up Game. All Rights Reserved.


#include "AI/EQS/EnvQueryTest_PickCouldBeTaken.h"

#include "EnvironmentQuery/Items/EnvQueryItemType_ActorBase.h"
#include "Pickups/STUBasePickup.h"

UEnvQueryTest_PickCouldBeTaken::UEnvQueryTest_PickCouldBeTaken(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    Cost = EEnvTestCost::Low;
    ValidItemType = UEnvQueryItemType_ActorBase::StaticClass();
    SetWorkOnFloatValues(false);
    
}

void UEnvQueryTest_PickCouldBeTaken::RunTest(FEnvQueryInstance& QueryInstance) const
{
    const auto Owner = QueryInstance.Owner.Get();
    BoolValue.BindData(Owner, QueryInstance.QueryID);
    auto WantsBeTakable = BoolValue.GetValue();
    
    for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
    {
        const auto Actor = GetItemActor(QueryInstance, It.GetIndex());
        const auto Pickup = Cast<ASTUBasePickup>(Actor);
        if (!Pickup) return;

        const auto CouldBeTaken = Pickup->CouldBeTaken();
        It.SetScore(TestPurpose, FilterType, CouldBeTaken, WantsBeTakable);
    }
}
