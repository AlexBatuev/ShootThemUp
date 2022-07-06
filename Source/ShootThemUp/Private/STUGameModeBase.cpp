// Shoot Them Up Game. All Rights Reserved.

#include "STUGameModeBase.h"

void ASTUGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    const int32 v = 0;
    if (v < 10)
    {
        for (auto i = 0; i < v; i++)
        {
            UE_LOG(LogTemp, Display, TEXT("index: %i"), i);
        }
    }
}
