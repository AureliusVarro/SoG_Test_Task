#include "Weapons/TP_AmmoAttributeSet.h"
#include "GameplayEffectExtension.h"


UTP_AmmoAttributeSet::UTP_AmmoAttributeSet()
{
}

void UTP_AmmoAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    if (Data.EvaluatedData.Attribute == GetShotgunAmmoAttribute())
    {
        // Handle stamina changes.
        SetShotgunAmmo(FMath::Clamp(GetShotgunAmmo(), 0.0f, GetMaxShotgunAmmo()));
    }

    if (Data.EvaluatedData.Attribute == GetPistolAmmoAttribute())
    {
        // Handle stamina changes.
        SetPistolAmmo(FMath::Clamp(GetPistolAmmo(), 0.0f, GetMaxPistolAmmo()));
    }
}