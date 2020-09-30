// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "TP_DamagetExecCalculation.generated.h"


/**
 * 
 */
UCLASS()
class TESTPROJECT_API UTP_DamagetExecCalculation : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
	
public:
	UTP_DamagetExecCalculation();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
