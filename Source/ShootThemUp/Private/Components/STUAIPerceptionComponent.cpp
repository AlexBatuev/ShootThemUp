// Shoot Them Up Game. All Rights Reserved.


#include "Components/STUAIPerceptionComponent.h"
#include "AIController.h"
#include "STUUtils.h"
#include "Components/STUHealthComponent.h"
#include "Perception/AISense_Sight.h"

AActor* USTUAIPerceptionComponent::GetClosestEnemy() const
{
    TArray<AActor*> PercieveActors;
    GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PercieveActors);
    if(PercieveActors.Num() == 0) return nullptr;

    const auto Controller = Cast<AAIController>(GetOwner());
    if (!Controller) return nullptr;

    const auto Pawn = Controller->GetPawn();
    if (!Pawn) return nullptr;

    float BestDistance = MAX_FLT;
    AActor* BestPawn = nullptr;

    for (const auto Actor : PercieveActors)
    {
        const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(Actor);

        const auto PercievePawn = Cast<APawn>(Actor);
        const auto AreEnemies = PercievePawn && STUUtils::AreEnemies(Controller, PercievePawn->Controller);
        
        if (HealthComponent && !HealthComponent->IsDead() && AreEnemies)
        {
            const auto Distance = (Actor->GetActorLocation() - Pawn->GetActorLocation()).Size();
            if (Distance < BestDistance)
            {
                BestDistance = Distance;
                BestPawn = Actor;
            }
        }
    }
    
    return BestPawn;
}
