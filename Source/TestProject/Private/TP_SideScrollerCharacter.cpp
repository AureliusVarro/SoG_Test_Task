// Copyright Epic Games, Inc. All Rights Reserved.

#include "TP_SideScrollerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "TP_AttributeSet.h"
#include "GameFramework/CharacterMovementComponent.h"

ATP_SideScrollerCharacter::ATP_SideScrollerCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Rotation of the character should not affect rotation of boom
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SocketOffset = FVector(0.f,0.f,75.f);
	CameraBoom->SetRelativeRotation(FRotator(0.f,180.f,0.f));

	// Create a camera and attach to boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	//AbilitySystemComponent
	AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));

	//AttributeSet
	AttributeSet = CreateDefaultSubobject<UTP_AttributeSet>(TEXT("AttributeSet"));

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

UAbilitySystemComponent* ATP_SideScrollerCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystem;
}

void ATP_SideScrollerCharacter::BeginPlay()
{
	Super::BeginPlay();

	AbilitySystem->InitAbilityActorInfo(this, this);

	if (AbilitySystem)
	{
		AddCharacterAbilities();
		InitializeAttributes();
		AddStartupEffects();

	}
}

void ATP_SideScrollerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	AbilitySystem->BindAbilityActivationToInputComponent(InputComponent, FGameplayAbilityInputBinds("ConfirmInput", "CancelInput", "ETP_AbilityInputID"));
}

void ATP_SideScrollerCharacter::InitializeAttributes()
{
	if (AbilitySystem && AttributeSet) {
		FGameplayEffectContextHandle EffectContext = AbilitySystem->MakeEffectContext();
		EffectContext.AddSourceObject(this);
		
		FGameplayEffectSpecHandle SpecHandle = AbilitySystem->MakeOutgoingSpec(DefaultAttributeEffect, 1, EffectContext);

		if (SpecHandle.IsValid()) {
			FActiveGameplayEffectHandle GEHandle = AbilitySystem->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
	}
}

void ATP_SideScrollerCharacter::AddStartupEffects()
{
	if (!AbilitySystem) {
		return;
	}

	FGameplayEffectContextHandle EffectContext = AbilitySystem->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	for (TSubclassOf<UGameplayEffect> GameplayEffect : StartupEffects)
	{
		FGameplayEffectSpecHandle SpecHandle = AbilitySystem->MakeOutgoingSpec(GameplayEffect, 1, EffectContext);
		if (SpecHandle.IsValid())
		{
			FActiveGameplayEffectHandle GEHandle = AbilitySystem->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
	}

}

void ATP_SideScrollerCharacter::AddCharacterAbilities_Implementation()
{
	// Grant abilities, but only on the server	
	if (IsValid(AbilitySystem))
	{
		for (TSubclassOf<UTP_GameplayAbility>& StartupAbility : CharacterAbilities)
		{
			AbilitySystem->GiveAbility(
				FGameplayAbilitySpec(StartupAbility, 1, static_cast<int32>(StartupAbility.GetDefaultObject()->InputID), this));
		}
	}

}

bool ATP_SideScrollerCharacter::AddCharacterAbilities_Validate()
{
	return true;
}