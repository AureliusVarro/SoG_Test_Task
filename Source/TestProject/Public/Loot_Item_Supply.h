// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TP_LootItemBase.h"
#include "Loot_Item_Supply.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API ALoot_Item_Supply : public ATP_LootItemBase
{
	GENERATED_BODY()

protected:

public: 
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item Propety")
	int32 impulse_Velocity;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item Propety")
	int32 value;
};
