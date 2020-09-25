// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemInterface.h"
#include "GameplayAbilitySpec.h"
#include "AbilitySystemComponent.h"
#include "../TP_SideScrollerCharacter.h"
#include "../../TestProject.h"
#include "TP_WeaponBase.generated.h"

UCLASS()
class TESTPROJECT_API ATP_WeaponBase : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATP_WeaponBase();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon")
	FGameplayTag WeaponTag;

	// Implement IAbilitySystemInterface
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	void SetOwningCharacter(ATP_SideScrollerCharacter* InOwningCharacter);

	virtual void AddAbilities();

	virtual void RemoveAbilities();

	// Called when the player equips this weapon
	virtual void Equip();

	virtual void Unequip();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
    virtual int32 GetClipAmmo() const;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
    virtual int32 GetMaxClipAmmo() const;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
    virtual void SetClipAmmo(int32 NewClipAmmo);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
    virtual void SetMaxClipAmmo(int32 NewMaxClipAmmo);

protected:
	UPROPERTY()
		UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
		USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
		ATP_SideScrollerCharacter* OwningCharacter;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
		TArray<TSubclassOf<UTP_GameplayAbility>> Abilities;

	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
		TArray<FGameplayAbilitySpecHandle> AbilitySpecHandles;

	// How much ammo in the clip the gun starts with
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Weapon|Ammo")
	int32 ClipAmmo;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Weapon|Ammo")
	int32 MaxClipAmmo;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



};
