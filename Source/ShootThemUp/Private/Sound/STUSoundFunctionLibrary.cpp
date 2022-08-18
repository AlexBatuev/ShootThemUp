// Shoot Them Up Game. All Rights Reserved.


#include "Sound/STUSoundFunctionLibrary.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUSoundFL, All, All);

void USTUSoundFunctionLibrary::SetSoundClassVolume(USoundClass* SoundClass, float volume)
{
    if(!SoundClass) return;

    SoundClass->Properties.Volume = FMath::Clamp(volume, 0.f, 1.f);
    UE_LOG(LogSTUSoundFL, Display, TEXT("Sound class voilume was changed: %s = %f"), *SoundClass->GetName(), SoundClass->Properties.Volume);
}

void USTUSoundFunctionLibrary::ToggleSoundClassVolume(USoundClass* SoundClass)
{
    if(!SoundClass) return;

    const auto NextVolume = SoundClass->Properties.Volume > 0 ? 0.f : 1.f;
    SetSoundClassVolume(SoundClass, NextVolume);
}
