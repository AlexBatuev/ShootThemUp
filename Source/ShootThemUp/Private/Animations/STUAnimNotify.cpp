// Shoot Them Up Game. All Rights Reserved.


#include "Animations/STUAnimNotify.h"

void USTUAnimNotify::Notify(USkeletalMeshComponent* MeshComponent, UAnimSequenceBase* Animation)
{
    Super::Notify(MeshComponent, Animation);
    OnNotified.Broadcast(MeshComponent);
}
