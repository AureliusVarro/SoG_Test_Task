// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/TP_CharacterBase.h"

#include "GameplayEffectTypes.h"

// Sets default values
ATP_CharacterBase::ATP_CharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//AbilitySystemComponent
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));

	//AttributeSet
	AttributeSet = CreateDefaultSubobject<UTP_AttributeSet>(TEXT("AttributeSet"));

}

UAbilitySystemComponent* ATP_CharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ATP_CharacterBase::AddCharacterAbilities()
{
	if (IsValid(AbilitySystemComponent))
	{
		for (TSubclassOf<UTP_GameplayAbility>& StartupAbility : CharacterAbilities)
		{
			AbilitySystemComponent->GiveAbility(
                FGameplayAbilitySpec(StartupAbility, 1, static_cast<int32>(StartupAbility.GetDefaultObject()->InputID), this));
		}
	}

}

void ATP_CharacterBase::InitializeAttributes()
{
	if (AbilitySystemComponent && AttributeSet) {
		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(this);
		
		FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributeEffect, 1, EffectContext);

		if (SpecHandle.IsValid()) {
			FActiveGameplayEffectHandle GEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
	}
}

void ATP_CharacterBase::AddStartupEffects()
{
	if (!AbilitySystemComponent)
	{
		return;
	}

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	for (TSubclassOf<UGameplayEffect> GameplayEffect : StartupEffects)
	{
		FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffect, 1, EffectContext);
		if (SpecHandle.IsValid())
		{
			FActiveGameplayEffectHandle GEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
	}

}

// Called when the game starts or when spawned
void ATP_CharacterBase::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		InitializeAttributes();
		AddCharacterAbilities();
		AddStartupEffects();
	}
	
}

// Called every frame
void ATP_CharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATP_CharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

