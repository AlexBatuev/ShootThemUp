// Shoot Them Up Game. All Rights Reserved.


#include "UI/STUGameDataWidget.h"
#include "STUGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Player/STUPlayerState.h"

int32 USTUGameDataWidget::GetRemainingRoundTime() const
{
    const auto GameMode = GetGameMode();
    return GameMode ? GameMode->GetElapsedRoundTime() : 0;
}

int32 USTUGameDataWidget::GetCurrentRound() const
{
    const auto GameMode = GetGameMode();
    return GameMode ? GameMode->GetCurrentRound() : 0;
}

int32 USTUGameDataWidget::GetTotalRounds() const
{
    const auto GameMode = GetGameMode();
    return GameMode ? GameMode->GetTotalRounds() : 0;
}

int32 USTUGameDataWidget::GetKillsCount() const
{
    const auto PlayerState = GetPlayerState();
    return PlayerState ? PlayerState->GetKillsCount() : 0;
}

int32 USTUGameDataWidget::GetDeathsCount() const
{
    const auto PlayerState = GetPlayerState();
    return PlayerState ? PlayerState->GetDeathsCount() : 0;
}

ASTUGameModeBase* USTUGameDataWidget::GetGameMode() const
{
    return GetWorld() ? Cast<ASTUGameModeBase>(UGameplayStatics::GetGameMode(GetWorld())) : nullptr;
}

ASTUPlayerState* USTUGameDataWidget::GetPlayerState() const
{
    return GetOwningPlayer() ? Cast<ASTUPlayerState>(GetOwningPlayer()->PlayerState) : nullptr;
}
