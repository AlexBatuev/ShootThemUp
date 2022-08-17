// Shoot Them Up Game. All Rights Reserved.


#include "UI/STUGoToMenuWidget.h"

#include "STUGameInstance.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogGoToMenuWidget, All, All);

void USTUGoToMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    
    if(GoToMenuButton)
    {
        GoToMenuButton->OnClicked.AddDynamic(this, &USTUGoToMenuWidget::OnGoToMenu);
    }
}

void USTUGoToMenuWidget::OnGoToMenu()
{
    if (!GetWorld()) return;

    const auto GameInstance = GetWorld()->GetGameInstance<USTUGameInstance>();
    if (!GameInstance) return;

    const auto MenuLevelName = GameInstance->GetMenuLevelName();
    if(MenuLevelName.IsNone())
    {
        UE_LOG(LogGoToMenuWidget, Error, TEXT("Menu level name is None"));
        return;
    }
    
    UGameplayStatics::OpenLevel(this, MenuLevelName);
}