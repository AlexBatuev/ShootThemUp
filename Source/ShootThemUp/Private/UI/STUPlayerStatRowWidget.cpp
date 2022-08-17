// Shoot Them Up Game. All Rights Reserved.


#include "UI/STUPlayerStatRowWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

void USTUPlayerStatRowWidget::SetPlayerName(const FText& Text) const
{
    if(!PlayerNameTextBlock) return;
    PlayerNameTextBlock->SetText(Text);
}

void USTUPlayerStatRowWidget::SetKills(const FText& Text) const
{
    if(!KillsTextBlock) return;
    KillsTextBlock->SetText(Text);
}

void USTUPlayerStatRowWidget::SetDeaths(const FText& Text) const
{
    if(!DeathsTextBlock) return;
    DeathsTextBlock->SetText(Text);
}

void USTUPlayerStatRowWidget::SetTeam(const FText& Text) const
{
    if(!TeamTextBlock) return;
    TeamTextBlock->SetText(Text);
}

void USTUPlayerStatRowWidget::SetPlayerIndicatorVisibility(const bool Visible) const
{
    if(!PlayerIndicatorImage) return;
    PlayerIndicatorImage->SetVisibility(Visible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void USTUPlayerStatRowWidget::SetTeamColor(const FLinearColor& Color) const
{
    if(!TeamImage) return;
    TeamImage->SetColorAndOpacity(Color);
}
