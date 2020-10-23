// Fill out your copyright notice in the Description page of Project Settings.


#include "TP_EnemyCharacterBase.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
//#include "Net/UnrealNetwork.h"
#include "GameplayTagContainer.h"
#include "..\Public\TP_EnemyCharacterBase.h"


ATP_EnemyCharacterBase::ATP_EnemyCharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//bIsDead = false;

	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Dead"));
	
}



// Called when the game starts or when spawned
void ATP_EnemyCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	

	if (AbilitySystemComponent)//TODO: error
	{
	
		// Called on server whenever a GE is applied to self. This includes instant and duration based GEs.
		AbilitySystemComponent->OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &ATP_EnemyCharacterBase::OnGameplayEffectApplied);
		// Attribute change callbacks
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute()).AddUObject(this, &ATP_EnemyCharacterBase::HealthChanged);
	}
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("GetBaseValue %f"), AttributeSet->Health.GetBaseValue()));
	
	
}

void ATP_EnemyCharacterBase::OnGameplayEffectApplied(UAbilitySystemComponent * Source, const FGameplayEffectSpec & Spec, FActiveGameplayEffectHandle Handle)
{
	//Instigate only player
	bool IsPlayer = Source->GetAvatarActor()->GetInstigatorController()->IsPlayerController();

	if (!IsPlayer)
	{
		return;
	}

	FGameplayTagContainer ContainTags;
	Spec.GetAllAssetTags(ContainTags);

	if (ContainTags.HasAny(InstigateTags) && !ASCSourceInstigator)
	{
		ASCSourceInstigator = Source;
		OnInstigateDelegate.Broadcast(ASCSourceInstigator);
	}

}


//void ATP_EnemyCharacterBase::Death_Implementation()
//{
//
//}

void ATP_EnemyCharacterBase::Death()
{
	UE_LOG(LogTemp, Warning, TEXT("dddddddddddddddddddddd"));
	OnEnemyDeathDelegate.Broadcast();
	//ASCSourceInstigate = nullptr;
	AbilitySystemComponent->OnGameplayEffectAppliedDelegateToSelf.RemoveAll(this);
}

void ATP_EnemyCharacterBase::HealthChanged(const FOnAttributeChangeData & Data)
{
	
	if (!IsAlive() && !AbilitySystemComponent->HasMatchingGameplayTag(DeadTag))
	{
		
		//damage from the effect
		if (Data.GEModData)
		{
			FGameplayEffectContextHandle Context = Data.GEModData->EffectSpec.GetContext();
			UAbilitySystemComponent* Source = Context.GetOriginalInstigatorAbilitySystemComponent();
			UAbilitySystemComponent* SourceAbilitySystemComponent = Context.GetOriginalInstigatorAbilitySystemComponent();
			//AActor* SourceActor = SourceAbilitySystemComponent ? SourceAbilitySystemComponent->AvatarActor : nullptr;
			if (SourceAbilitySystemComponent)
			{
				ASCSourceDeath = SourceAbilitySystemComponent;
			}

		}
		
		Death();
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

bool ATP_EnemyCharacterBase::IsAlive() const
{
	return AttributeSet->GetHealth() > 0.0f;
}

UAbilitySystemComponent * ATP_EnemyCharacterBase::GetASCSourceInstigator()
{
	return ASCSourceInstigator;
	
}

UAbilitySystemComponent * ATP_EnemyCharacterBase::GetASCSourceDeath()
{
	return ASCSourceDeath;

}

void ATP_EnemyCharacterBase::SetASCSourceInstigator(UAbilitySystemComponent * value)
{
	ASCSourceInstigator = value;
}



int ATP_EnemyCharacterBase::GetPointsPerKill()
{
	return PointsPerKill;
}

//int ATP_EnemyCharacterBase::GetBaseDamage()
//{
//	return BaseDamage;
//}
