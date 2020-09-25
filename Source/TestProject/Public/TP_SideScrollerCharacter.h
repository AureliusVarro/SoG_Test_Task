// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "TP_GameplayAbility.h"
#include "TP_AttributeSet.h"
#include "../TestProject.h"
#include "TP_SideScrollerCharacter.generated.h"

class ATP_WeaponBase;

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

	UPROPERTY()
	ATP_WeaponBase* CurrentWeapon;

	virtual void BeginPlay() override;


public:

	ATP_SideScrollerCharacter();

	// Default abilities for this Character. These will be removed on Character death and regiven if Character respawns.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
		TArray<TSubclassOf<class UTP_GameplayAbility>> CharacterAbilities;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Weapon")
		FName WeaponAttachPoint;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
		TArray<TSubclassOf <class ATP_WeaponBase>> WeaponClasses;

	UPROPERTY()
	TArray<ATP_WeaponBase*> Weapons;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	FGameplayTag CurrentWeaponTag;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
    ATP_WeaponBase* GetCurrentWeapon() const;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
    virtual void NextWeapon();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
    virtual void PreviousWeapon();

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

	virtual void InitializeWeapons();

	// Grant abilities on the Server. The Ability Specs will be replicated to the owning client.
	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation)
	void AddCharacterAbilities();

	FName GetWeaponAttachPoint();

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	//FORCEINLINE class UAbilitySystemComponent* GetAbilitySystem() const { return AbilitySystem; }
};
