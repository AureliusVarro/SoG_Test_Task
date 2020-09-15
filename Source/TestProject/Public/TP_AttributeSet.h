// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "TP_AttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
/**
 * 
 */
UCLASS()
class TESTPROJECT_API UTP_AttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:

	UTP_AttributeSet();

	// AttributeSet Overrides
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Current stamina, used to execute special abilities. Capped by MaxStamina.
	UPROPERTY(BlueprintReadOnly, Category = "Stamina", ReplicatedUsing = OnRep_Stamina)
		FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UTP_AttributeSet, Stamina)

		// MaxStamina is its own attribute since GameplayEffects may modify it
		UPROPERTY(BlueprintReadOnly, Category = "Stamina", ReplicatedUsing = OnRep_MaxStamina)
		FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UTP_AttributeSet, MaxStamina)

		// Stamina regen rate will passively increase Stamina every second
		UPROPERTY(BlueprintReadOnly, Category = "Stamina", ReplicatedUsing = OnRep_StaminaRegenRate)
		FGameplayAttributeData StaminaRegenRate;
	ATTRIBUTE_ACCESSORS(UTP_AttributeSet, StaminaRegenRate)

protected:

	// Helper function to proportionally adjust the value of an attribute when it's associated max attribute changes.
	// (i.e. When MaxHealth increases, Health increases by an amount that maintains the same percentage as before)
	void AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty);

	UFUNCTION()
		virtual void OnRep_Stamina(const FGameplayAttributeData& OldStamina);

	UFUNCTION()
		virtual void OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina);

	UFUNCTION()
		virtual void OnRep_StaminaRegenRate(const FGameplayAttributeData& OldStaminaRegenRate);

};
