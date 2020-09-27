#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "TP_AmmoAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
/**
 * 
 */
UCLASS()
class TESTPROJECT_API UTP_AmmoAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:

	UTP_AmmoAttributeSet();

	// AttributeSet Overrides
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	UPROPERTY(BlueprintReadOnly, Category = "Weapon | Ammo")
	FGameplayAttributeData ShotgunAmmo;
	ATTRIBUTE_ACCESSORS(UTP_AmmoAttributeSet, ShotgunAmmo)

	UPROPERTY(BlueprintReadOnly, Category = "Weapon | Ammo")
	FGameplayAttributeData MaxShotgunAmmo;
	ATTRIBUTE_ACCESSORS(UTP_AmmoAttributeSet, MaxShotgunAmmo)

	UPROPERTY(BlueprintReadOnly, Category = "Weapon | Ammo")
	FGameplayAttributeData PistolAmmo;
	ATTRIBUTE_ACCESSORS(UTP_AmmoAttributeSet, PistolAmmo)
	
    UPROPERTY(BlueprintReadOnly, Category = "Weapon | Ammo")
	FGameplayAttributeData MaxPistolAmmo;
	ATTRIBUTE_ACCESSORS(UTP_AmmoAttributeSet, MaxPistolAmmo)
};