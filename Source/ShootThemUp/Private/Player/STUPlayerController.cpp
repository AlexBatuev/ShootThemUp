// Shoot Them Up Game. All Rights Reserved.

#include "Player/STUPlayerController.h"

#include "STUGameInstance.h"
#include "STUGameModeBase.h"
#include "Components/STURespawnComponent.h"
#include "GameFramework/GameModeBase.h"

ASTUPlayerController::ASTUPlayerController()
{
    RespawnComponent = CreateDefaultSubobject<USTURespawnComponent>("RespawnComponent");
}

void ASTUPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (GetWorld())
    {
        const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->OnGameStateChange.AddUObject(this, &ASTUPlayerController::OnGameStateChanged);
        }
    }
}

void ASTUPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if(!InputComponent) return;

    InputComponent->BindAction("Pause", IE_Pressed, this, &ASTUPlayerController::OnPause);
    InputComponent->BindAction("Mute", IE_Pressed, this, &ASTUPlayerController::OnMuteSound);
}

void ASTUPlayerController::OnPause()
{
    if(!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

    GetWorld()->GetAuthGameMode()->SetPause(this);
}

void ASTUPlayerController::OnGameStateChanged(ESTUGameState State)
{
    if (State == ESTUGameState::InProgress)
    {
        SetInputMode(FInputModeGameOnly());
        bShowMouseCursor = false;
    }
    else
    {
        SetInputMode(FInputModeUIOnly());
        bShowMouseCursor = true;
    }
}

void ASTUPlayerController::OnMuteSound()
{
    if(!GetWorld()) return;

    const auto GameInstance = GetWorld()->GetGameInstance<USTUGameInstance>();
    if (!GameInstance) return;

    GameInstance->ToggleVolume();
}

// void ASTUPlayerController::OnPossess(APawn* InPawn)
// {
//     Super::OnPossess(InPawn);
//
//     OnNewPawn.Broadcast(InPawn);
// }
