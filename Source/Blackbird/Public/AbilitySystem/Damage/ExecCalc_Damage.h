// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "ExecCalc_Damage.generated.h"

/**
 * 
 */
UCLASS()
class BLACKBIRD_API UExecCalc_Damage : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	virtual void Execute_Implementation(
		const FGameplayEffectCustomExecutionParameters& ExecutionParams,
		FGameplayEffectCustomExecutionOutput& OutExecutionOutput
	) const override;

private:
	float CalculateBaseDamage(
		const FGameplayEffectCustomExecutionParameters& ExecutionParams,
		const FAggregatorEvaluateParameters& EvaluateParameters
	) const;
	bool IsRadialDamage(const FGameplayEffectCustomExecutionParameters& ExecutionParams) const;
	void ApplyRadialDamage(const FGameplayEffectCustomExecutionParameters& ExecutionParams, float& OutRadialDamage) const;
	bool IsAttackBlockedByTarget(
		const FGameplayEffectCustomExecutionParameters& ExecutionParams,
		const FAggregatorEvaluateParameters& EvaluateParameters
	) const;
	float GetTargetEffectiveDefense(
		const FGameplayEffectCustomExecutionParameters& ExecutionParams,
		const FAggregatorEvaluateParameters& EvaluateParameters
	) const;
	bool IsCriticalHitOnTarget(
		const FGameplayEffectCustomExecutionParameters& ExecutionParams,
		const FAggregatorEvaluateParameters& EvaluateParameters
	) const;
};
