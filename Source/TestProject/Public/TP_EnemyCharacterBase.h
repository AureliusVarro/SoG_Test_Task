// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AttributeSet.h"
#include "TP_AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "../TestProject.h"
#include "Characters/TP_CharacterBase.h"
#include "Components/StaticMeshComponent.h"
#include "TP_EnemyCharacterBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEnemyDeathDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInstigateDelegate, UAbilitySystemComponent*, ASCSourceInstigator);

UCLASS(config=Game)
class TESTPROJECT_API ATP_EnemyCharacterBase : public ATP_CharacterBase
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    ATP_EnemyCharacterBase();

	UPROPERTY(BlueprintAssignable, Category = "Abilities | Attributes")
		FOnEnemyDeathDelegate OnEnemyDeathDelegate;

	UPROPERTY(BlueprintAssignable, Category = "Abilities | Attributes")
		FOnInstigateDelegate OnInstigateDelegate;

    //UFUNCTION(BlueprintNativeEvent)
    void Death();

    //virtual void Death_Implementation();

    // Attribute changed callbacks
    virtual void HealthChanged(const FOnAttributeChangeData& Data);


protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Source ASC Instigator
	UAbilitySystemComponent* ASCSourceInstigator = nullptr;

	//Source ASC killer
	UAbilitySystemComponent* ASCSourceDeath = nullptr;

	FGameplayTag DeadTag;

	//this effects that should instigate enemy 
	UPROPERTY(EditAnywhere, Category = "EnemyParameters")
		FGameplayTagContainer InstigateTags;

	/*UPROPERTY(EditAnywhere, Category = "EnemyParameters")
		int BaseDamage = 0;*/

	UPROPERTY(EditAnywhere, Category = "EnemyParameters")
		int PointsPerKill=0;

	//UPROPERTY(EditAnywhere, Category = "EnemyParameters")
	//	float RangeAttack = 0.0f;

	UFUNCTION()
		void OnGameplayEffectApplied(UAbilitySystemComponent* Source, const FGameplayEffectSpec& Spec, FActiveGameplayEffectHandle Handle);

    //UPROPERTY()
   // bool bIsDead;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Abilities | Attributes")
		bool IsAlive() const;


	UFUNCTION(BlueprintCallable, BlueprintPure)
		UAbilitySystemComponent* GetASCSourceInstigator();

	//UFUNCTION(BlueprintCallable)
	UFUNCTION(BlueprintCallable, BlueprintPure)
		UAbilitySystemComponent* GetASCSourceDeath();

	//void SetSourceAttack(UAbilitySystemComponent* DamageSource);
	UFUNCTION(BlueprintCallable)
		void SetASCSourceInstigator(UAbilitySystemComponent* ASCSourceInstigator);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		int GetPointsPerKill();

	/*UFUNCTION(BlueprintCallable, BlueprintPure)
		int GetBaseDamage();*/
	
};
