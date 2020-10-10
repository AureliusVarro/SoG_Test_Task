// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AttributeSet.h"
#include "TP_AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "../TestProject.h"
#include "TP_EnemyCharacterBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEnemyDeathDelegate);

UCLASS()
class TESTPROJECT_API ATP_EnemyCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATP_EnemyCharacterBase();

	UPROPERTY(BlueprintAssignable, Category = "Abilities | Attributes")
		FOnEnemyDeathDelegate OnEnemyDeathDelegate;

	UFUNCTION(BlueprintNativeEvent)
		void Death();

	virtual void Death_Implementation();

	// Attribute changed callbacks
	virtual void HealthChanged(const FOnAttributeChangeData& Data);




protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	bool bIsDead;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Inherited via IAbilitySystemInterface

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"))
		class UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities | Attributes", meta = (AllowPrivateAccess = "true"))
		class UTP_AttributeSet* AttributeSet;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
		TArray<TSubclassOf<class UGameplayAbility>> EnemyAbilities;

	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation)
		void AddCharacterAbilities();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Abilities | Attributes")
		TSubclassOf<class UGameplayEffect> DefaultAttributeEffect;

	// These effects are only applied one time on startup
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
		TArray<TSubclassOf<class UGameplayEffect>> StartupEffects;

	virtual void AddStartupEffects();
	
	virtual void InitializeAttributes();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;



};
