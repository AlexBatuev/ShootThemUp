// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUPlayerStatRowWidget.generated.h"

class UImage;
class UTextBlock;

UCLASS()
class SHOOTTHEMUP_API USTUPlayerStatRowWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    void SetPlayerName(const FText& Text) const;
    void SetKills(const FText& Text) const;
    void SetDeaths(const FText& Text) const;
    void SetTeam(const FText& Text) const;
    void SetPlayerIndicatorVisibility(bool Visible) const;
    void SetTeamColor(const FLinearColor& Color) const;
	
protected:
    UPROPERTY(meta = (BindWidget))
    UTextBlock* PlayerNameTextBlock;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* KillsTextBlock;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* DeathsTextBlock;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* TeamTextBlock;
        
    UPROPERTY(meta = (BindWidget))
    UImage* PlayerIndicatorImage;

    UPROPERTY(meta = (BindWidget))
    UImage* TeamImage;
};
