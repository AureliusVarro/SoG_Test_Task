// Fill out your copyright notice in the Description page of Project Settings.


#include "TP_DamagetExecCalculation.h"
#include "AbilitySystemComponent.h"
#include "TP_AttributeSet.h"


struct TP_DamageStatics
{
	//The DECLARE_ATTRIBUTE_CAPTUREDEF macro actually only declares two variables. The variable names are dependent on the input, however. Here they will be HealthProperty(which is a UPROPERTY pointer)
	//and HealthDef(which is a FGameplayEffectAttributeCaptureDefinition).
	DECLARE_ATTRIBUTE_CAPTUREDEF(Health);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	//DECLARE_ATTRIBUTE_CAPTUREDEF(Damage);

	//DECLARE_ATTRIBUTE_CAPTUREDEF(AttackMultiplier); //Here AttackMultiplierProperty and AttackMultiplierDef. I hope you get the drill.
	//DECLARE_ATTRIBUTE_CAPTUREDEF(DefenseMultiplier);
	//DECLARE_ATTRIBUTE_CAPTUREDEF(BaseAttackPower);

	TP_DamageStatics()
	{
		// We define the values of the variables we declared now. In this example, HealthProperty will point to the Health attribute in the UMyAttributeSet on the receiving target of this execution. The last parameter is a bool, and determines if we snapshot the attribute's value at the time of definition.
		DEFINE_ATTRIBUTE_CAPTUREDEF(UTP_AttributeSet, Health, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UTP_AttributeSet, Armor, Target, false);
		//DEFINE_ATTRIBUTE_CAPTUREDEF(UTP_AttributeSet, Damage, Source, false);

		//This here is a different example: We still take the attribute from UMyAttributeSet, but this time it is BaseAttackPower, and we look at the effect's source for it. We also want to snapshot is because the effect's strength should be determined during its initial creation. A projectile wouldn't change
		//damage values depending on the source's stat changes halfway through flight, after all.
		//DEFINE_ATTRIBUTE_CAPTUREDEF(UTP_AttributeSet, BaseAttackPower, Source, true);

		//The same rules apply for the multiplier attributes too.
		//DEFINE_ATTRIBUTE_CAPTUREDEF(UTP_AttributeSet, AttackMultiplier, Source, true);
		//DEFINE_ATTRIBUTE_CAPTUREDEF(UTP_AttributeSet, DefenseMultiplier, Target, false);
	}
};

static const TP_DamageStatics& DamageStatics()
{
	static TP_DamageStatics DStatics;
	return DStatics;
}

UTP_DamagetExecCalculation::UTP_DamagetExecCalculation()
{
	//RelevantAttributesToCapture - это массив, содержащий все атрибуты, которые вы хотите захватить, без исключений.
    //Благодаря этому, позже в AttemptCalculateCapturedAttributeMagnitude() методе мы сможем запросить данные параметры
	RelevantAttributesToCapture.Add(DamageStatics().HealthDef);
	InvalidScopedModifierAttributes.Add(DamageStatics().HealthDef);

	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	InvalidScopedModifierAttributes.Add(DamageStatics().ArmorDef);

	//RelevantAttributesToCapture.Add(DamageStatics().DamageDef);
	//InvalidScopedModifierAttributes.Add(DamageStatics().DamageDef);

}

void UTP_DamagetExecCalculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters & ExecutionParams, OUT FGameplayEffectCustomExecutionOutput & OutExecutionOutput) const
{
	// Мы помещаем компоненты AbilitySystemComponents в маленькие вспомогательные переменные. Не обязательно, но это помогает нам не печатать так много.
	UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();
	UAbilitySystemComponent* SourceAbilitySystemComponent = ExecutionParams.GetSourceAbilitySystemComponent();
	
	//
	AActor* SourceActor = SourceAbilitySystemComponent ? SourceAbilitySystemComponent->AvatarActor : nullptr;
	AActor* TargetActor = TargetAbilitySystemComponent ? TargetAbilitySystemComponent->AvatarActor : nullptr;

	//получаем спецификацию эффекта который порадил этот объект
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	// Gather the tags from the source and target as that can affect which buffs should be used
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	// Мы используем эти теги для создания структуры FAggregatorEvaluateParameters,
	//которая нам понадобится для получения значений наших захваченных атрибутов позже в этой функции.
	FAggregatorEvaluateParameters EvaluationParameters;
	//EvaluationParameters.SourceTags = SourceTags;
	//EvaluationParameters.TargetTags = TargetTags;
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("World delta for current frame equals %s"), *EvaluationParameters.SourceTags->ToString()));

	float Health = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().HealthDef, EvaluationParameters, Health);
	Health = FMath::Max<float>(Health, 0.0f);


	float Armor = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef, EvaluationParameters, Armor);
	Armor = FMath::Max<float>(Armor, 0.0f);

	float Damage = 0.0f;
	// Capture optional damage value set on the damage GE as a CalculationModifier under the ExecutionCalculation
	// Хорошо, здесь мы получаем захваченное значение атрибута в нашу функцию. Damage ().
	//DamageDef - это определение атрибута, который мы хотим получить, мы определили
	//EvaluationParameters чуть выше нас
	//а Damage - это переменная, в которую мы поместим полученное значение (переменная Damage, которую мы только что объявили)
	//ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().DamageDef, EvaluationParameters, Damage);

	// Add SetByCaller damage if it exists
	// Аттрибут damage по умолчанию = 0, damage устанавливается в абилках с помощью SetByCallerMagnitude  
	Damage += FMath::Max<float>(Spec.GetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Damage")), false, -1.0f), 0.0f);

	float UnmitigatedDamage = Damage; // Can multiply any damage boosters here
	float OldArmor = Armor;
	Armor = FMath::Clamp (Armor-Damage,0.0f, Armor);
	float MitigatedDamage = UnmitigatedDamage - (OldArmor - Armor) * 0.5f;
	





	
	


	if (MitigatedDamage > 0.f)
	{
		// Set the Target's damage meta attribute
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatics().HealthProperty, EGameplayModOp::Additive, -MitigatedDamage));
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatics().ArmorProperty, EGameplayModOp::Additive, -UnmitigatedDamage));
	}

}
