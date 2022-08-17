// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUGameDataWidget.generated.h"

class ASTUPlayerState;
class ASTUGameModeBase;

UCLASS()
class SHOOTTHEMUP_API USTUGameDataWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    int32 GetRemainingRoundTime() const;
    
    UFUNCTION(BlueprintCallable, Category = "UI")
    int32 GetCurrentRound() const;
    
    UFUNCTION(BlueprintCallable, Category = "UI")
    int32 GetTotalRounds() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    int32 GetDeathsCount() const;

private:
    ASTUGameModeBase* GetGameMode() const;
    ASTUPlayerState* GetPlayerState() const;
};
