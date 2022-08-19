// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "STUCoreTypes.h"
#include "GameFramework/GameMode.h"
#include "GameFramework/GameModeBase.h"
#include "STUGameModeBase.generated.h"

class AAIController;

UCLASS()
class SHOOTTHEMUP_API ASTUGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

public:
    ASTUGameModeBase();

    FOnGameStateChangeSignature OnGameStateChange;

    virtual void StartPlay() override;
    virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

    void OnKill(const AController* KillerController, AController* VictimController);

    int32 GetCurrentRound() const { return CurrentRound; }
    int32 GetTotalRounds() const { return GameData.RoundsCount; }
    //int32 GetGameData() const { return GameData; }
    int32 GetElapsedRoundTime() const { return RoundCountDown; }
    void RespawnPlayer(AController* Controller);

    virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate) override;
    virtual bool ClearPause() override;

protected:
    UPROPERTY(EditDefaultsOnly, Category="Game")
    TSubclassOf<AAIController> AIControllerClass;

    UPROPERTY(EditDefaultsOnly, Category="Game")
    TSubclassOf<APawn> AIPawnClass;

    UPROPERTY(EditDefaultsOnly, Category="Game")
    FGameData GameData;

private:
    ESTUGameState GameState = ESTUGameState::WaitingToStart;
    int32 CurrentRound = 1;
    int32 RoundCountDown = 0;
    FTimerHandle GameRoundTimerHandle;
    
    void SpawnBots();
    void StartRound();
    void GameTimerUpdate();

    void ResetAllPlayers();
    void ResetPlayer(AController* Controller);

    void CreateTeamsInfo() const;
    FLinearColor DetermineColorByTeamId(int32 TeamId) const;
    void SetPlayerColor(const AController* Controller) const;

    void LogPlayerInfo() const;

    void StartRespawn(AController* Controller);

    void GameOver();

    void SetGameState(ESTUGameState NewState);

    void StopAllFire();
};
