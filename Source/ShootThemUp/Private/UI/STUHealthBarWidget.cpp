// Shoot Them Up Game. All Rights Reserved.


#include "UI/STUHealthBarWidget.h"

#include "Components/ProgressBar.h"

void USTUHealthBarWidget::UpdateHealthPercent(float Percent)
{
    if(!HealthBar) return;

    const auto HealthBarVisibility = (Percent > PercentVisibilityThreshold || FMath::IsNearlyZero(Percent)) ? ESlateVisibility::Hidden : ESlateVisibility::Visible;
    HealthBar->SetVisibility(HealthBarVisibility);

    const auto HealthBarColor = Percent > PercentColorThreshold ? GoodColor : BadColor;
    HealthBar->SetFillColorAndOpacity(HealthBarColor);
    
    HealthBar->SetPercent(Percent);
}
