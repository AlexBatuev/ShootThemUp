// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "STUCoreTypes.h"
#include "Blueprint/UserWidget.h"
#include "STULevelItemWidget.generated.h"

class UImage;
class UTextBlock;
class UButton;

UCLASS()
class SHOOTTHEMUP_API USTULevelItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    FOnLevelSelectedSignature OnLevelSelected;

    void SetLevelData(const FLevelData& NewLevelData);
    FLevelData GetLevelData() const { return LevelData; }
    void SetSelected(bool IsSelected) const;

protected:
    UPROPERTY(meta = (BindWidget))
    UButton* LevelSelectButton;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* LevelNameTextBlock;

    UPROPERTY(meta = (BindWidget))
    UImage* LevelImage;

    UPROPERTY(meta = (BindWidget))
    UImage* FrameImage;

    virtual void NativeOnInitialized() override;

private:
    FLevelData LevelData;

    UFUNCTION()
    void OnClicked();

    UFUNCTION()
    void OnLevelItemHovered();

    UFUNCTION()
    void OnLevelItemUnhovered();
    
};
