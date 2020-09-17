#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "TP_SideScrollerCharacter.h"
#include "../TestProject.h"
#include "TP_GameplayAbility.generated.h"

/**
 *
 */
UCLASS()
class TESTPROJECT_API UTP_GameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UTP_GameplayAbility();

	// Abilities with this set will automatically activate when the input is pressed
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
		ETP_AbilityInputID InputID;
};
