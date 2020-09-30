// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "TP_EnemyAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


/**
 * 
 */
UCLASS()
class TESTPROJECT_API UTP_EnemyAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UTP_EnemyAttributeSet();

	UPROPERTY(BlueprintReadOnly, Category = "Damage")
		FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UTP_EnemyAttributeSet, Damage)

		UPROPERTY(BlueprintReadOnly, Category = "Heath")
		FGameplayAttributeData Heath;
	ATTRIBUTE_ACCESSORS(UTP_EnemyAttributeSet, Heath)

		UPROPERTY(BlueprintReadOnly, Category = "WalkSpeed")
		FGameplayAttributeData WalkSpeed;
	ATTRIBUTE_ACCESSORS(UTP_EnemyAttributeSet, WalkSpeed)

};
