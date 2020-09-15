// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "TP_AttributeSet.h"
#include "TP_SideScrollerCharacter.generated.h"

UENUM(BlueprintType)
enum class AbilityInput : uint8
{
	Pickup	UMETA(DisplayName = "Pickup"),	// This will be bound via key bindings in engine as "Pickup"
	JumpAbility	UMETA(DisplayName = "JumpAbility"),
	Sprint UMETA(DisplayName = "Sprint")
};

UCLASS(config=Game)
class ATP_SideScrollerCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"))
		class UAbilitySystemComponent* AbilitySystem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities | Attributes", meta = (AllowPrivateAccess = "true"))
		class UTP_AttributeSet* AttributeSet;

protected:

	virtual void BeginPlay() override;

public:

	ATP_SideScrollerCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
		class TSubclassOf<UGameplayAbility> Pickup;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
		class TSubclassOf<UGameplayAbility> JumpAbility;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
		class TSubclassOf<UGameplayAbility> TurnAbility;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
		class TSubclassOf<UGameplayAbility> LedgeClimbAbility;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
		class TSubclassOf<UGameplayAbility> SprintAbility;

	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void InitializeAttributes();

	//Effect to setup the default attributes
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Abilities | Attributes")
		TSubclassOf<class UGameplayEffect> DefaultAttributeEffect;

	// These effects are only applied one time on startup
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
		TArray<TSubclassOf<class UGameplayEffect>> StartupEffects;

	virtual void AddStartupEffects();

	// Grant abilities on the Server. The Ability Specs will be replicated to the owning client.
	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation)
	void AddCharacterAbilities();

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	//FORCEINLINE class UAbilitySystemComponent* GetAbilitySystem() const { return AbilitySystem; }
};
