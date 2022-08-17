#pragma once
#include <Runtime/Engine/Classes/GameFramework/Pawn.h>

#include "Player/STUPlayerState.h"

class STUUtils
{
public:
	template<typename T>
    static T* GetSTUPlayerComponent(AActor* PlayerPawn)
	{
        if (!PlayerPawn)
            return nullptr;

        const auto Component = PlayerPawn->GetComponentByClass(T::StaticClass());
        return Cast<T>(Component);
	}

    static bool AreEnemies(const AController* Controller1, const AController* Controller2)
	{
	    if(!Controller1 || !Controller2 || Controller1 == Controller2) return false;

	    const auto PlayerState1 = Cast<ASTUPlayerState>(Controller1->PlayerState);
	    const auto PlayerState2 = Cast<ASTUPlayerState>(Controller2->PlayerState);

	    return PlayerState1 && PlayerState2 && PlayerState1->GetTeamId() != PlayerState2->GetTeamId();
	}

    static FText TextFromInt(const int32 Number)
	{
	    return FText::FromString(FString::FromInt(Number));
	}
};
