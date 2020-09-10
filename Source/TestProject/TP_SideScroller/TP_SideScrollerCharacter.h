// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "TP_SideScrollerCharacter.generated.h"

UENUM(BlueprintType)
enum class AbilityInput : uint8
{
	Pickup	UMETA(DisplayName = "Pickup"),	// This will be bound via key bindings in engine as "Pickup"
	JumpAbility	UMETA(DisplayName = "JumpAbility"),
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

protected:
	

	virtual void BeginPlay() override;

public:
	// The ability in our "Ability 1" slot.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
		class TSubclassOf<UGameplayAbility> Pickup;

	// The ability in our "Ability 2" slot.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
		class TSubclassOf<UGameplayAbility> JumpAbility;

	// The ability in our "Ability 2" slot.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
		class TSubclassOf<UGameplayAbility> TurnAbility;

	ATP_SideScrollerCharacter();

	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Grant abilities on the Server. The Ability Specs will be replicated to the owning client.
	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation)
	void AddCharacterAbilities();

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	//FORCEINLINE class UAbilitySystemComponent* GetAbilitySystem() const { return AbilitySystem; }
};
