#pragma once

class AnimUtils
{
public:
    template <typename T>
    static T* FindNotifyByClass(UAnimSequenceBase* Animation)
    {
        if (!Animation)
            return nullptr;

        const auto& Notifies = Animation->Notifies;
        for (const auto& Notify : Notifies)
        {
            const auto AnimationNotify = Cast<T>(Notify.Notify);
            if (AnimationNotify)
            {
                return AnimationNotify;
            }
        }

        return nullptr;
    }
};
