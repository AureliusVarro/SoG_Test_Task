// Fill out your copyright notice in the Description page of Project Settings.


#include "TP_EnemyCharacterBase.h"

// Sets default values
ATP_EnemyCharacterBase::ATP_EnemyCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AbilitySystemComponent=CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
	//AttributeSet
	//AttributeSet = CreateDefaultSubobject<UTP_EnemyAttributeSet>(TEXT("AttributeSet"));
	
}

// Called when the game starts or when spawned
void ATP_EnemyCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	

	if (AbilitySystemComponent)
	{
		AddCharacterAbilities();
		InitializeAttributes();
		AddStartupEffects();

	}
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("World delta for current frame equals %f"), AttributeSet->Health.GetBaseValue()));
	
	
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

void ATP_EnemyCharacterBase::AddCharacterAbilities_Implementation()
{
	// Grant abilities, but only on the server	
	if (IsValid(AbilitySystemComponent))
	{
		for (TSubclassOf<UGameplayAbility>& StartupAbility : EnemyAbilities)
		{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(StartupAbility, 1));
		}
	}

}

bool ATP_EnemyCharacterBase::AddCharacterAbilities_Validate()
{
	return true;
}

void ATP_EnemyCharacterBase::AddStartupEffects()
{
	if (!AbilitySystemComponent) {
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