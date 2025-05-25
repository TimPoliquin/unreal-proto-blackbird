// Copyright Alien Shores 2025


#include "AbilitySystem/Effect/BlackbirdDamageEffectParams.h"
#include "AbilitySystem/Config/BlackbirdDamageConfig.h"
#include "AbilitySystem/Config/BlackbirdRadialDamageParams.h"

void FBlackbirdDamageEffectParams::FillFromDamageConfig(const FBlackbirdDamageConfig& DamageConfig)
{
	DeathImpulseMagnitude = DamageConfig.DeathImpulseMagnitude;
	KnockbackChance = DamageConfig.KnockbackChance;
	KnockbackForceMagnitude = DamageConfig.KnockbackForceMagnitude;
	const FBlackbirdRadialDamageParams& RadialDamageParams = DamageConfig.GetRadialDamageParams();
	FillFromRadialDamageEffectParams(RadialDamageParams);
}

void FBlackbirdDamageEffectParams::FillFromRadialDamageEffectParams(const FBlackbirdRadialDamageParams& RadialDamageParams)
{
	if (RadialDamageParams.bIsRadialDamage)
	{
		bIsRadialDamage = RadialDamageParams.bIsRadialDamage;
		RadialDamageInnerRadius = RadialDamageParams.RadialDamageInnerRadius;
		RadialDamageOuterRadius = RadialDamageParams.RadialDamageOuterRadius;
		RadialDamageOrigin = RadialDamageParams.RadialDamageOrigin;
	}
}

bool FBlackbirdDamageEffectParams::RollForKnockbackChance() const
{
	return FMath::RandRange(1, 100) < KnockbackChance;
}
