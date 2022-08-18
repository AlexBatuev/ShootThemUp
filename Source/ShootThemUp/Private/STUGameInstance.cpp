// Shoot Them Up Game. All Rights Reserved.


#include "STUGameInstance.h"

#include "Sound/STUSoundFunctionLibrary.h"

void USTUGameInstance::ToggleVolume()
{
    USTUSoundFunctionLibrary::ToggleSoundClassVolume(MasterSoundClass);
}
