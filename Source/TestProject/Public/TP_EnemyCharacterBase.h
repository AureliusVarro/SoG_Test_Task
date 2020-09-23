// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystemComponent.h"
#include "TP_GameplayAbility.h"
#include "TP_EnemyAttributeSet.h"
#include "TP_AttributeSet.h"
#include "GameFramework/Pawn.h"
#include "TP_EnemyCharacterBase.generated.h"

UCLASS()
class TESTPROJECT_API ATP_EnemyCharacterBase : public APawn , public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATP_EnemyCharacterBase();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCharacterMovementComponent* CharacterMovementComponent;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	

	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	// Inherited via IAbilitySystemInterface
	virtual UAbilitySystemComponent * GetAbilitySystemComponent() const override;

	virtual void InitializeAttributes();
	
	void AddCharacterAbilities();
	
	UPROPERTY(EditAnywhere)
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Abilities")
	TArray<TSubclassOf<UTP_GameplayAbility>> AbilityCharacter;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category="Attributes")
	class UTP_EnemyAttributeSet* AttributeSet;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Abilities")
		TSubclassOf<class UGameplayEffect> DefaultAttributeEffect;
	
	

};
