// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "STUPlayerState.generated.h"

UCLASS()
class SHOOTTHEMUP_API ASTUPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
    void SetTemId(int Id) { TeamId = Id; }
    int32 GetTeamId() const { return TeamId; }
    void SetTeamColor(const FLinearColor& Color) { TeamColor = Color; }
    FLinearColor GetTeamColor() const { return TeamColor; }

    void AddKill() { KillsCount++; }
    int32 GetKillsCount() const { return KillsCount; }
    
    void AddDeath() { DeathsCount++; }
    int32 GetDeathsCount() const { return DeathsCount; }

    void LogInfo() const;
    
private:
    int32 TeamId;
    FLinearColor TeamColor;

    int32 KillsCount = 0;
    int32 DeathsCount = 0;
};
