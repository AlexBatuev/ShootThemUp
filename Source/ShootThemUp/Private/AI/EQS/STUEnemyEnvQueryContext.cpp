// Shoot Them Up Game. All Rights Reserved.


#include "AI/EQS/STUEnemyEnvQueryContext.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"

void USTUEnemyEnvQueryContext::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
    Super::ProvideContext(QueryInstance, ContextData);

    const auto Owner = Cast<AActor>(QueryInstance.Owner.Get());
    const auto Blackboard = UAIBlueprintHelperLibrary::GetBlackboard(Owner);
    if (!Blackboard) return;

    
    const auto Actor = Blackboard->GetValueAsObject(EnemyActorKeyName);
    UEnvQueryItemType_Actor::SetContextHelper(ContextData, Cast<AActor>(Actor));

    
}
