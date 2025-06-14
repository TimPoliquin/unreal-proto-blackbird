// Copyright Alien Shores 2025


#include "AbilitySystem/Ability/BlackbirdDamageGameplayAbility.h"

#include "AbilitySystem/BlackbirdAbilitySystemLibrary.h"
#include "AbilitySystem/Attribute/BlackbirdAttributeSet.h"

FBlackbirdDamageEffectParams UBlackbirdDamageGameplayAbility::MakeDamageEffectParamsFromClassDefaults(
	AActor* TargetActor,
	const FVector& RadialDamageOrigin,
	const bool bOverrideKnockbackDirection,
	const FVector& InKnockbackDirectionOverride,
	const bool bOverrideDeathImpulse,
	const FVector& InDeathImpulseDirectionOverride,
	const bool bOverridePitch,
	const float PitchOverride
) const
{
	return UBlackbirdAbilitySystemLibrary::MakeCustomDamageEffectParams(
		GetAvatarActorFromActorInfo(),
		TargetActor,
		DamageEffectClass,
		DamageConfig,
		GetAbilityLevel(),
		RadialDamageOrigin,
		bOverrideKnockbackDirection,
		InKnockbackDirectionOverride,
		bOverrideDeathImpulse,
		InDeathImpulseDirectionOverride,
		bOverridePitch,
		PitchOverride
	);
}

int32 UBlackbirdDamageGameplayAbility::GetDamageAtLevel(const int32 AbilityLevel) const
{
	return DamageConfig.GetDamageAtLevel(AbilityLevel);
}

float UBlackbirdDamageGameplayAbility::GetEnergyCost(const float InLevel) const
{
	if (GetCostGameplayEffect())
	{
		for (const FGameplayModifierInfo& Mod : GetCostGameplayEffect()->Modifiers)
		{
			if (Mod.Attribute == UBlackbirdAttributeSet::GetEnergyAttribute())
			{
				float ManaCost = 0.f;
				// TODO this assumes a static value.
				Mod.ModifierMagnitude.GetStaticMagnitudeIfPossible(InLevel, ManaCost);
				return ManaCost;
			}
		}
	}
	return 0.f;
}

float UBlackbirdDamageGameplayAbility::GetHeatCost_Implementation(const float InLevel) const
{
	if (GetCostGameplayEffect())
	{
		for (const FGameplayModifierInfo& Mod : GetCostGameplayEffect()->Modifiers)
		{
			if (Mod.Attribute == UBlackbirdAttributeSet::GetAvailableHeatAttribute())
			{
				float ManaCost = 0.f;
				// TODO this assumes a static value.
				Mod.ModifierMagnitude.GetStaticMagnitudeIfPossible(InLevel, ManaCost);
				return ManaCost;
			}
		}
	}
	return 0.f;
}

float UBlackbirdDamageGameplayAbility::GetCooldown(const float InLevel) const
{
	if (const UGameplayEffect* CooldownEffect = GetCooldownGameplayEffect())
	{
		float Cooldown = 0.f;
		CooldownEffect->DurationMagnitude.GetStaticMagnitudeIfPossible(InLevel, Cooldown);
		return Cooldown;
	}
	return 0.f;
}
