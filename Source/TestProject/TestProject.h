// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ETP_AbilityInputID : uint8
{
	None			UMETA(DisplayName = "None"),
	Confirm			UMETA(DisplayName = "Confirm"),
	Cancel			UMETA(DisplayName = "Cancel"),
	Pickup			UMETA(DisplayName = "Pickup"),	// This will be bound via key bindings in engine as "Pickup"
	JumpAbility		UMETA(DisplayName = "JumpAbility"),
	Sprint			UMETA(DisplayName = "Sprint"),
	Fire			UMETA(DisplayName = "Fire"),
	Reload			UMETA(DisplayName = "Reload"),
	Aim				UMETA(DisplayName = "Aim")
};

