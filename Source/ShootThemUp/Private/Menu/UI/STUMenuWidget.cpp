// Shoot Them Up Game. All Rights Reserved.


#include "Menu/UI/STUMenuWidget.h"

#include "STUGameInstance.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUMenuWidget, All, All);

void USTUMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if(StartGameButton)
    {
        StartGameButton->OnClicked.AddDynamic(this, &USTUMenuWidget::OnStartGame);
    }
    
    if(QuitGameButton)
    {
        QuitGameButton->OnClicked.AddDynamic(this, &USTUMenuWidget::OnQuitGame);
    }

    InitLevelItems();
}

void USTUMenuWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
    Super::OnAnimationFinished_Implementation(Animation);

    if (Animation != HideAnimation) return;
    
    const auto GameInstance = GetStuGameInstance();
    if (!GameInstance) return;
    
    UGameplayStatics::OpenLevel(this, GameInstance->GetStartupLevel().LevelName);
}

void USTUMenuWidget::OnStartGame()
{
    PlayAnimation(HideAnimation);
}

void USTUMenuWidget::OnQuitGame()
{
    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

void USTUMenuWidget::InitLevelItems()
{
    const auto GameInstance = GetStuGameInstance();
    if (!GameInstance) return;
    
    checkf(GameInstance->GetLevelsData().Num() != 0, TEXT("Levels data must be not empty"));

    if(!LevelItemsBox) return;
    LevelItemsBox->ClearChildren();
    
    for (auto LevelData : GameInstance->GetLevelsData())
    {
        const auto Widget = CreateWidget<USTULevelItemWidget>(GetWorld(), LevelItemWidgetClass);
        if (!Widget) continue;

        Widget->SetLevelData(LevelData);
        Widget->OnLevelSelected.AddUObject(this, &USTUMenuWidget::OnLevelSelected);

        LevelItemsBox->AddChild(Widget);
        LevelItemWidgets.Add(Widget);
    }

    if (GameInstance->GetStartupLevel().LevelName.IsNone())
    {
        OnLevelSelected(GameInstance->GetLevelsData()[0]);
    }
    else
    {
        OnLevelSelected(GameInstance->GetStartupLevel());
    }
}

void USTUMenuWidget::OnLevelSelected(const FLevelData& LevelData)
{
    const auto GameInstance = GetStuGameInstance();
    if(!GameInstance) return;

    GameInstance->SetStartupLevel(LevelData);

    for (const auto Widget : LevelItemWidgets)
    {
        if (Widget)
        {
            const auto IsSelected = LevelData.LevelName == Widget->GetLevelData().LevelName;
            Widget->SetSelected(IsSelected);
        }
    }
}

USTUGameInstance* USTUMenuWidget::GetStuGameInstance() const
{
    if(!GetWorld()) return nullptr;

    return GetWorld()->GetGameInstance<USTUGameInstance>();
}
