// Fill out your copyright notice in the Description page of Project Settings.


#include "TP_EnemyCharacterBase.h"
#include "..\Public\TP_EnemyCharacterBase.h"

// Sets default values
ATP_EnemyCharacterBase::ATP_EnemyCharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bIsDead = false;
	
}



// Called when the game starts or when spawned
void ATP_EnemyCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	

	if (AbilitySystemComponent)//TODO: error
	{
		// Attribute change callbacks
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute()).AddUObject(this, &ATP_EnemyCharacterBase::HealthChanged);
	}
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("World delta for current frame equals %f"), AttributeSet->Health.GetBaseValue()));
	
	
}

void ATP_EnemyCharacterBase::Death_Implementation()
{
	if(!bIsDead)
	{
		OnEnemyDeathDelegate.Broadcast();
		bIsDead = true;
	}
	
	
}

void ATP_EnemyCharacterBase::HealthChanged(const FOnAttributeChangeData & Data)
{

	if (Data.NewValue <= 0)
		Death();

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