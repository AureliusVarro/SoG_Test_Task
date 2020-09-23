// Fill out your copyright notice in the Description page of Project Settings.


#include "TP_EnemyCharacterBase.h"

// Sets default values
ATP_EnemyCharacterBase::ATP_EnemyCharacterBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CharacterMovementComponent=CreateAbstractDefaultSubobject<UCharacterMovementComponent>(TEXT("CharacterMovementComponent"));
	AbilitySystemComponent=CreateAbstractDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
	AttributeSet=CreateAbstractDefaultSubobject<UTP_EnemyAttributeSet>("Attribute");
}

// Called when the game starts or when spawned
void ATP_EnemyCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	AddCharacterAbilities();
	InitializeAttributes();

	
}



void ATP_EnemyCharacterBase::InitializeAttributes()
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

// Called every frame
void ATP_EnemyCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATP_EnemyCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UAbilitySystemComponent * ATP_EnemyCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ATP_EnemyCharacterBase::AddCharacterAbilities()
{
	if (IsValid(AbilitySystemComponent))
	{
		for (TSubclassOf<UTP_GameplayAbility>& StartupAbility : AbilityCharacter)
		{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(StartupAbility.GetDefaultObject(), 1));
		}
	}
}

