// Shoot Them Up Game. All Rights Reserved.

#include "AI/STUAICharacter.h"

#include "BrainComponent.h"
#include "AI/STUAIController.h"
#include "Components/STUAIWeaponComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ASTUAICharacter::ASTUAICharacter(const FObjectInitializer& ObjInit):Super(ObjInit.SetDefaultSubobjectClass<USTUAIWeaponComponent>("WeaponComponent"))
{
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    AIControllerClass = ASTUAIController::StaticClass();

    bUseControllerRotationYaw = false;
    if (GetCharacterMovement())
    {
        GetCharacterMovement()->bUseControllerDesiredRotation = true;
        GetCharacterMovement()->RotationRate.Yaw = 200.f;
    }

}

void ASTUAICharacter::OnDeath()
{
    Super::OnDeath();

    const auto AIController = Cast<AAIController>(Controller);
    if (AIController && AIController->BrainComponent)
    {
        AIController->BrainComponent->Cleanup();
    }
}
