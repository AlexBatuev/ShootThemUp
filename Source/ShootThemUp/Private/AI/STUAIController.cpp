// Shoot Them Up Game. All Rights Reserved.


#include "AI/STUAIController.h"
#include "AI/STUAICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/STUAIPerceptionComponent.h"
#include "Components/STURespawnComponent.h"

ASTUAIController::ASTUAIController()
{
    AIPerceptionComponent = CreateDefaultSubobject<USTUAIPerceptionComponent>("PerceptionComponent");
    SetPerceptionComponent(*AIPerceptionComponent);

    RespawnComponent = CreateDefaultSubobject<USTURespawnComponent>("RespawnComponent");

    bWantsPlayerState = true;
}

void ASTUAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    const auto AiCharacter = Cast<ASTUAICharacter>(InPawn);
    if(AiCharacter)
    {
        RunBehaviorTree(AiCharacter->BehaviorTree);
    }
}

void ASTUAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    SetFocus(GetFocusOnActor());
}

AActor* ASTUAIController::GetFocusOnActor()
{
    if(!GetBlackboardComponent())
        return nullptr;

    return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}
