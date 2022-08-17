// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "STUBaseWidget.h"
#include "STUGameOverWidget.generated.h"

class UButton;
class UVerticalBox;
enum class ESTUGameState : uint8;

UCLASS()
class SHOOTTHEMUP_API USTUGameOverWidget : public USTUBaseWidget
{
	GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UVerticalBox* PlayerStatBox;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
    TSubclassOf<UUserWidget> PlayerStatRowWidgetClass;

    UPROPERTY(meta = (BindWidget))
    UButton* ResetLevelButton;

    virtual void NativeOnInitialized() override;
    
private:
    void OnGameStateChanged(ESTUGameState State) const;
    void UpdatePlayerStat() const;

    UFUNCTION()
    void OnResetLevel();
};
