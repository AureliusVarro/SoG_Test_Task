// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystemComponent.h"
#include "Weapons/TP_WeaponBase.h"

// Sets default values
ATP_WeaponBase::ATP_WeaponBase()
{
	// Set this actor to never tick
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(FName("WeaponMesh"));
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponMesh->CastShadow = true;
	WeaponMesh->SetVisibility(true, true);
	WeaponMesh->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPose;

}

UAbilitySystemComponent* ATP_WeaponBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ATP_WeaponBase::SetOwningCharacter(ATP_SideScrollerCharacter* InOwningCharacter)
{
	OwningCharacter = InOwningCharacter;
	if (OwningCharacter)
	{
		// Called when added to inventory
		AbilitySystemComponent = Cast<UAbilitySystemComponent>(OwningCharacter->GetAbilitySystemComponent());
		SetOwner(InOwningCharacter);
		FName AttachPoint = OwningCharacter->GetWeaponAttachPoint();
		WeaponMesh->AttachToComponent(OwningCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, AttachPoint);
		//AttachToComponent(OwningCharacter->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		
	}
	else
	{
		AbilitySystemComponent = nullptr;
		SetOwner(nullptr);
		DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	}
}

void ATP_WeaponBase::AddAbilities()
{
	if (!IsValid(OwningCharacter) || !OwningCharacter->GetAbilitySystemComponent())
	{
		return;
	}

	UAbilitySystemComponent* ASC = Cast<UAbilitySystemComponent>(OwningCharacter->GetAbilitySystemComponent());

	if (!ASC)
	{
		UE_LOG(LogTemp, Error, TEXT("%s %s ASC is null"), *FString(__FUNCTION__), *GetName());
		return;
	}

	for (TSubclassOf<UTP_GameplayAbility>& Ability : Abilities)
	{
		AbilitySpecHandles.Add(ASC->GiveAbility(
			FGameplayAbilitySpec(Ability, 1, static_cast<int32>(Ability.GetDefaultObject()->InputID), this)));
	}
}

void ATP_WeaponBase::RemoveAbilities()
{
	if (!IsValid(OwningCharacter) || !OwningCharacter->GetAbilitySystemComponent())
	{
		return;
	}

	UAbilitySystemComponent* ASC = Cast<UAbilitySystemComponent>(OwningCharacter->GetAbilitySystemComponent());

	if (!ASC)
	{
		return;
	}

	for (FGameplayAbilitySpecHandle& SpecHandle : AbilitySpecHandles)
	{
		ASC->ClearAbility(SpecHandle);
	}
}

void ATP_WeaponBase::Equip()
{
	if (!OwningCharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("%s %s OwningCharacter is nullptr"), *FString(__FUNCTION__), *GetName());
		return;
	}

	FName AttachPoint = OwningCharacter->GetWeaponAttachPoint();

	if (WeaponMesh)
	{
		WeaponMesh->AttachToComponent(OwningCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, AttachPoint);
		//WeaponMesh->SetRelativeLocation(WeaponMeshEquippedRelativeLocation);
		//WeaponMesh->SetRelativeRotation(FRotator(0, 0, -90.0f));
		WeaponMesh->SetVisibility(true, true);
	}

}

// Called when the game starts or when spawned
void ATP_WeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

