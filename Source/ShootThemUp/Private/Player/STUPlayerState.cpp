// Shoot Them Up Game. All Rights Reserved.


#include "Player/STUPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUPlayerState, All, All);

void ASTUPlayerState::LogInfo() const
{
    UE_LOG(LogSTUPlayerState, Display, TEXT("TeamId: %i, Kills: %i, Deaths: %i"), TeamId, KillsCount, DeathsCount);
}
