// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "STUGameInstance.h"
#include "STULevelItemWidget.h"
#include "UI/STUBaseWidget.h"
#include "STUMenuWidget.generated.h"

class USoundCue;
class UHorizontalBox;
class UButton;

UCLASS()
class SHOOTTHEMUP_API USTUMenuWidget : public USTUBaseWidget
{
	GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UButton* StartGameButton;

    UPROPERTY(meta = (BindWidget))
    UButton* QuitGameButton;

    UPROPERTY(meta = (BindWidget))
    UHorizontalBox* LevelItemsBox;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> LevelItemWidgetClass;

    UPROPERTY(meta = (BindWidgetAnim), Transient)
    UWidgetAnimation* HideAnimation;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
    USoundCue* StartGameSound;
    
    virtual void NativeOnInitialized() override;
    virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;
    
private:
    UPROPERTY()
    TArray<USTULevelItemWidget*> LevelItemWidgets;
    
    UFUNCTION()
    void OnStartGame();

    UFUNCTION()
    void OnQuitGame();

    void InitLevelItems();
    void OnLevelSelected(const FLevelData& LevelData);
    USTUGameInstance* GetStuGameInstance() const;
};
