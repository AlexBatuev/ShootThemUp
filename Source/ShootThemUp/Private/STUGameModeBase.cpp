// Shoot Them Up Game. All Rights Reserved.

#include "STUGameModeBase.h"

#include "AIController.h"
#include "EngineUtils.h"
#include "STUGameInstance.h"
#include "STUUtils.h"
#include "Components/STURespawnComponent.h"
#include "Player/STUBaseCharacter.h"
#include "Player/STUPlayerController.h"
#include "Player/STUPlayerState.h"
#include "UI/STUGameHUD.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUGameModeBase, All, All);

constexpr static int32 MinRoundTimeForRespawn = 10;

ASTUGameModeBase::ASTUGameModeBase()
{
    DefaultPawnClass = ASTUBaseCharacter::StaticClass();
    PlayerControllerClass = ASTUPlayerController::StaticClass();
    HUDClass = ASTUGameHUD::StaticClass();
    PlayerStateClass = ASTUPlayerController::StaticClass();
}

void ASTUGameModeBase::StartPlay()
{
    Super::StartPlay();
    
    SpawnBots();
    CreateTeamsInfo();
    
    CurrentRound = 1;
    StartRound();

    SetGameState(ESTUGameState::InProgress);
}

UClass* ASTUGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
    if(InController && InController->IsA<AAIController>())
    {
        return AIPawnClass;
    }
    return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void ASTUGameModeBase::OnKill(const AController* KillerController, AController* VictimController)
{
    const auto KillerPlayerState = KillerController ? Cast<ASTUPlayerState>(KillerController->PlayerState) : nullptr;
    const auto VictimPlayerState = VictimController ? Cast<ASTUPlayerState>(VictimController->PlayerState) : nullptr;

    if (KillerPlayerState)
    {
        KillerPlayerState->AddKill();
    }
    if (VictimPlayerState)
    {
        VictimPlayerState->AddDeath();
    }

    StartRespawn(VictimController);
}

void ASTUGameModeBase::RespawnPlayer(AController* Controller)
{
    ResetPlayer(Controller);
}

bool ASTUGameModeBase::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
    const auto PauseState = Super::SetPause(PC, CanUnpauseDelegate);
    if (PauseState)
    {
        SetGameState(ESTUGameState::Pause);
    }
    return PauseState;
}

bool ASTUGameModeBase::ClearPause()
{
    const auto ClearResult = Super::ClearPause();
    if (ClearResult)
    {
        SetGameState(ESTUGameState::InProgress);
    }
    return ClearResult;
}

void ASTUGameModeBase::SpawnBots()
{
    if(!GetWorld()) return;

    for (int32 i = 0; i < GameData.PlayersCount - 1; i++)
    {
        FActorSpawnParameters SpawnInfo;
        SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        const auto Controller = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
        RestartPlayer(Controller);
    }
}

void ASTUGameModeBase::StartRound()
{
    RoundCountDown = GameData.RoundTime;
    GetWorldTimerManager().SetTimer(GameRoundTimerHandle, this, &ASTUGameModeBase::GameTimerUpdate, 1.f, true);
}

void ASTUGameModeBase::GameTimerUpdate()
{
    UE_LOG(LogSTUGameModeBase, Display, TEXT("Time: %i / Round: %i/%i"), RoundCountDown, CurrentRound, GameData.RoundsCount);

    // const auto TimerRate = GetWorldTimerManager().GetTimerRate(GameRoundTimerHandle);
    // RoundCountDown -= TimerRate;
    
    if(--RoundCountDown == 0)
    {
        GetWorldTimerManager().ClearTimer(GameRoundTimerHandle);

        if(CurrentRound + 1 <= GameData.RoundsCount)
        {
            CurrentRound++;
            ResetAllPlayers();
            StartRound();
        }
        else
        {
            GameOver();
        }
    }
}

void ASTUGameModeBase::ResetAllPlayers()
{
    if(!GetWorld()) return;

    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        ResetPlayer(It->Get());
    }
}

void ASTUGameModeBase::ResetPlayer(AController* Controller)
{
    if (Controller && Controller->GetPawn())
    {
        Controller->GetPawn()->Reset();
    }
    RestartPlayer(Controller);
    SetPlayerColor(Controller);
}

void ASTUGameModeBase::CreateTeamsInfo() const
{
    if(!GetWorld()) return;

    int32 TeamId = 1;
    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();
        if (!Controller) continue;

        const auto PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);
        if (!PlayerState) continue;

        PlayerState->SetTemId(TeamId);
        PlayerState->SetTeamColor(DetermineColorByTeamId(TeamId));
        PlayerState->SetPlayerName(Controller->IsPlayerController() ? "Player" : "Bot");
        SetPlayerColor(Controller);

        TeamId = TeamId == 1 ? 2 : 1;
    }
}

FLinearColor ASTUGameModeBase::DetermineColorByTeamId(int32 TeamId) const
{
    if(TeamId - 1 < GameData.TeamColors.Num())
    {
        return GameData.TeamColors[TeamId - 1];        
    }
    
    UE_LOG(LogSTUGameModeBase, Display, TEXT("No color for tema id: %i, set to default: %s"), TeamId, *GameData.DefaultTeamColor.ToString());
    return GameData.DefaultTeamColor;
}

void ASTUGameModeBase::SetPlayerColor(const AController* Controller) const
{
    if (!Controller) return;

    const auto Character = Cast<ASTUBaseCharacter>(Controller->GetPawn());
    if (!Character) return;

    const auto PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);
    if (!PlayerState) return;

    Character->SetColor(PlayerState->GetTeamColor());    
}

void ASTUGameModeBase::LogPlayerInfo() const
{
    if(!GetWorld()) return;

    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();
        if (!Controller) continue;

        const auto PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);
        if (!PlayerState) continue;
        
        PlayerState->LogInfo();
    }
}

void ASTUGameModeBase::StartRespawn(AController* Controller)
{
    const auto RespawnAvailable = RoundCountDown > MinRoundTimeForRespawn + GameData.RespawnTime;
    if(!RespawnAvailable) return;
    
    const auto RespawnComponent = STUUtils::GetSTUPlayerComponent<USTURespawnComponent>(Controller);
    if(!RespawnComponent) return;

    RespawnComponent->Respawn(GameData.RespawnTime);
}

void ASTUGameModeBase::GameOver()
{
    UE_LOG(LogSTUGameModeBase, Display, TEXT("===== GAME OVER ====="));
    LogPlayerInfo();

    for (const auto Pawn : TActorRange<APawn>(GetWorld()))
    {
        if (Pawn)
        {
            Pawn->TurnOff();
            Pawn->DisableInput(nullptr);            
        }
    }
    SetGameState(ESTUGameState::GameOver);
}

void ASTUGameModeBase::SetGameState(ESTUGameState NewState)
{
    if (GameState == NewState) return;

    GameState = NewState;
    OnGameStateChange.Broadcast(GameState);    
}
