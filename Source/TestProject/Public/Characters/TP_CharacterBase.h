// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "TP_AttributeSet.h"
#include "GameFramework/Character.h"
#include "TP_CharacterBase.generated.h"

UCLASS()
class TESTPROJECT_API ATP_CharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATP_CharacterBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities", meta = (AllowPrivateAccess = "true"))
	class UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities | Attributes", meta = (AllowPrivateAccess = "true"))
	class UTP_AttributeSet* AttributeSet;

protected:

	//Effect to setup the default attributes
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Abilities | Attributes")
	TSubclassOf<class UGameplayEffect> DefaultAttributeEffect;

	virtual void InitializeAttributes();
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
