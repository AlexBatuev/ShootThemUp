// Shoot Them Up Game. All Rights Reserved.

#include "UI/STUGameHUD.h"
#include "STUGameModeBase.h"
#include "Engine/Canvas.h"
#include "UI/STUBaseWidget.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUGameHUD, All, All);

void ASTUGameHUD::DrawHUD()
{
    Super::DrawHUD();
}

void ASTUGameHUD::BeginPlay()
{
    Super::BeginPlay();

    GameWidgets.Add(ESTUGameState::InProgress, CreateWidget<USTUBaseWidget>(GetWorld(), PlayerHUDWidgetClass));
    GameWidgets.Add(ESTUGameState::Pause, CreateWidget<USTUBaseWidget>(GetWorld(), PauseWidgetClass));
    GameWidgets.Add(ESTUGameState::GameOver, CreateWidget<USTUBaseWidget>(GetWorld(), GameOverWidgetClass));

    for (const auto WidgetPair : GameWidgets)
    {
        const auto Widget = WidgetPair.Value;
        if (!Widget) continue;

        Widget->AddToViewport();
        Widget->SetVisibility(ESlateVisibility::Hidden);        
    }
    
    if (GetWorld())
    {
        const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->OnGameStateChange.AddUObject(this, &ASTUGameHUD::OnGameStateChanged);
        }
    }
}

void ASTUGameHUD::DrawCrossHair()
{
    const TInterval<float> Center(Canvas->SizeX * 0.5f, Canvas->SizeY * 0.5f);

    constexpr auto HalfLineSize = 10.f;
    constexpr auto LineThickness = 2.f;
    const auto LineColor = FLinearColor::Green;

    DrawLine(Center.Min - HalfLineSize, Center.Max, Center.Min + HalfLineSize, Center.Max, LineColor, LineThickness);
    DrawLine(Center.Min, Center.Max - HalfLineSize, Center.Min, Center.Max + HalfLineSize, LineColor, LineThickness);
}

void ASTUGameHUD::OnGameStateChanged(ESTUGameState State)
{
    if(CurrentWidget)
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
    }
    if(GameWidgets.Contains(State))
    {
        CurrentWidget = GameWidgets[State];
    }
    if(CurrentWidget)
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Visible);
        CurrentWidget->Show();
    }
    
    UE_LOG(LogSTUGameHUD, Display, TEXT("Game state changed: %s"), *UEnum::GetValueAsString(State));
}
