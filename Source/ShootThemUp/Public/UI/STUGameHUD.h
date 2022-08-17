// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "STUCoreTypes.h"
#include "GameFramework/HUD.h"
#include "STUGameHUD.generated.h"

class USTUBaseWidget;

UCLASS()
class SHOOTTHEMUP_API ASTUGameHUD : public AHUD
{
    GENERATED_BODY()

public:
    virtual void DrawHUD() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PauseWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> GameOverWidgetClass;
    
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    TMap<ESTUGameState, USTUBaseWidget*> GameWidgets;

    UPROPERTY()
    USTUBaseWidget* CurrentWidget;
    
    void DrawCrossHair();
    void OnGameStateChanged(ESTUGameState State);
};
