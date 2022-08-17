// Shoot Them Up Game. All Rights Reserved.


#include "Menu/UI/STULevelItemWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void USTULevelItemWidget::SetLevelData(const FLevelData& NewLevelData)
{
    LevelData = NewLevelData;

    if (LevelNameTextBlock)
    {
        LevelNameTextBlock->SetText(FText::FromName(LevelData.LevelDisplayName));
    }

    if (LevelImage)
    {
        LevelImage->SetBrushFromTexture(LevelData.LevelThumb);
    }
}

void USTULevelItemWidget::SetSelected(const bool IsSelected) const
{
    if(LevelImage)
    {
        LevelImage->SetColorAndOpacity(IsSelected ? FLinearColor::Red : FLinearColor::White);
    }
}

void USTULevelItemWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if(LevelSelectButton)
    {
        LevelSelectButton->OnClicked.AddDynamic(this, &USTULevelItemWidget::OnClicked);
        LevelSelectButton->OnHovered.AddDynamic(this, &USTULevelItemWidget::OnLevelItemHovered);
        LevelSelectButton->OnUnhovered.AddDynamic(this, &USTULevelItemWidget::OnLevelItemUnhovered);
    }
}

void USTULevelItemWidget::OnClicked()
{
    OnLevelSelected.Broadcast(LevelData);
}

void USTULevelItemWidget::OnLevelItemHovered()
{
    if(FrameImage)
    {
        FrameImage->SetVisibility(ESlateVisibility::Visible);
    }
}

void USTULevelItemWidget::OnLevelItemUnhovered()
{
    if(FrameImage)
    {
        FrameImage->SetVisibility(ESlateVisibility::Hidden);
    }
}
