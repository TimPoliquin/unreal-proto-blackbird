// Copyright Alien Shores 2025


#include "AbilitySystem/Damage/ExecCalc_Damage.h"

#include "AbilitySystem/BlackbirdAbilitySystemLibrary.h"
#include "AbilitySystem/Damage/DamageableInterface.h"
#include "AbilitySystem/Attribute/BlackbirdAttributeSet.h"
#include "AbilitySystem/Attribute/BlackbirdAttributeTags.h"
#include "Kismet/GameplayStatics.h"

struct BlackbirdDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Defense);
	DECLARE_ATTRIBUTE_CAPTUREDEF(AvailableHeat);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalChance);

	TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition> TagsToCaptureDefs;

	BlackbirdDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBlackbirdAttributeSet, Defense, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBlackbirdAttributeSet, AvailableHeat, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBlackbirdAttributeSet, CriticalChance, Source, false);

		const FBlackbirdAttributeTags& Tags = FBlackbirdAttributeTags::Get();

		TagsToCaptureDefs.Add(Tags.Attributes_Primary_Defense, DefenseDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Primary_CriticalChance, CriticalChanceDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Vital_AvailableHeat, AvailableHeatDef);
	}
};

static const BlackbirdDamageStatics& DamageStatics()
{
	// static singleton 
	static BlackbirdDamageStatics DStatics;
	return DStatics;
};

void UExecCalc_Damage::Execute_Implementation(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput
) const
{
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	FGameplayEffectContextHandle EffectContextHandle = Spec.GetContext();
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	// Get Damage Set by Caller Magnitude
	float Damage = CalculateBaseDamage(ExecutionParams, EvaluateParameters);
	if (IsRadialDamage(ExecutionParams))
	{
		ApplyRadialDamage(ExecutionParams, Damage);
	}
	// If the attack was blocked (based on shields), cut the damage in half, and transfer to heat.
	if (IsAttackBlockedByTarget(ExecutionParams, EvaluateParameters))
	{
		Damage *= .5f;
		UBlackbirdAbilitySystemLibrary::SetIsBlockedHit(EffectContextHandle, true);
	}
	// Reduce damage by a percentage based on target's effective armor
	Damage *= (100 - GetTargetEffectiveDefense(ExecutionParams, EvaluateParameters)) / 100.f;
	// if the attack is a critical hit, increase the damage by the critical hit damage
	if (IsCriticalHitOnTarget(ExecutionParams, EvaluateParameters))
	{
		Damage = Damage * 2.f;
		UBlackbirdAbilitySystemLibrary::SetIsCriticalHit(EffectContextHandle, true);
	}

	const FGameplayModifierEvaluatedData EvaluatedData(
		UBlackbirdBasicAttributeSet::GetMeta_IncomingDamageAttribute(),
		EGameplayModOp::Additive,
		Damage
	);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}

float UExecCalc_Damage::CalculateBaseDamage(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	const FAggregatorEvaluateParameters& EvaluateParameters
) const
{
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	const float Damage = Spec.GetSetByCallerMagnitude(FBlackbirdAttributeTags::Get().Attributes_Meta_IncomingDamage, false);
	const FGameplayEffectAttributeCaptureDefinition& DefenseDef = DamageStatics().DefenseDef;
	float Resistance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		DefenseDef,
		EvaluateParameters,
		Resistance
	);
	Resistance = FMath::Clamp(Resistance, 0.f, 100.f);
	return Damage * (100.f - Resistance) / 100.f;
}

bool UExecCalc_Damage::IsRadialDamage(const FGameplayEffectCustomExecutionParameters& ExecutionParams) const
{
	return UBlackbirdAbilitySystemLibrary::IsRadialDamage(ExecutionParams.GetOwningSpec().GetContext());
}

void UExecCalc_Damage::ApplyRadialDamage(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	float& OutRadialDamage
) const
{
	const FGameplayEffectSpec Spec = ExecutionParams.GetOwningSpec();
	const UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();
	AActor* TargetActor = TargetAbilitySystemComponent
		                      ? TargetAbilitySystemComponent->GetAvatarActor()
		                      : nullptr;
	const UAbilitySystemComponent* SourceAbilitySystemComponent = ExecutionParams.GetSourceAbilitySystemComponent();
	AActor* SourceActor = SourceAbilitySystemComponent
		                      ? SourceAbilitySystemComponent->GetAvatarActor()
		                      : nullptr;
	if (IDamageableInterface* DamageableInterface = Cast<IDamageableInterface>(TargetActor))
	{
		const FGameplayEffectContextHandle EffectContextHandle = Spec.GetContext();
		DamageableInterface->GetOnDamageDelegate().AddLambda(
			[&](const float DamageAmount)
			{
				OutRadialDamage = DamageAmount;
			}
		);
		UGameplayStatics::ApplyRadialDamageWithFalloff(
			TargetActor,
			OutRadialDamage,
			0.f,
			UBlackbirdAbilitySystemLibrary::GetRadialDamageOrigin(EffectContextHandle),
			UBlackbirdAbilitySystemLibrary::GetRadialDamageInnerRadius(EffectContextHandle),
			UBlackbirdAbilitySystemLibrary::GetRadialDamageOuterRadius(EffectContextHandle),
			1.f,
			UDamageType::StaticClass(),
			TArray<AActor*>(),
			SourceActor,
			nullptr
		);
	}
}

bool UExecCalc_Damage::IsAttackBlockedByTarget(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	const FAggregatorEvaluateParameters& EvaluateParameters
) const
{
	// TODO - determine if attack was blocked based on target shields
	return false;
}

float UExecCalc_Damage::GetTargetEffectiveDefense(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	const FAggregatorEvaluateParameters& EvaluateParameters
) const
{
	return 0.f;
}

bool UExecCalc_Damage::IsCriticalHitOnTarget(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	const FAggregatorEvaluateParameters& EvaluateParameters
) const
{
	float SourceCriticalHitChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		DamageStatics().CriticalChanceDef,
		EvaluateParameters,
		SourceCriticalHitChance
	);
	SourceCriticalHitChance = FMath::Max<float>(SourceCriticalHitChance, 0.f);
	const float CriticalHitCalculation = FMath::RandRange(1, 100);
	return CriticalHitCalculation <= SourceCriticalHitChance;
}
