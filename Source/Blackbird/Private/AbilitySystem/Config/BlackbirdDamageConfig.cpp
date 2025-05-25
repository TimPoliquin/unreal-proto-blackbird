// Copyright Alien Shores 2025


#include "AbilitySystem/Config/BlackbirdDamageConfig.h"

#include "AbilitySystem/Config/BlackbirdRadialDamageParams.h"

FBlackbirdRadialDamageParams FBlackbirdDamageConfig::GetRadialDamageParams() const
{
	FBlackbirdRadialDamageParams DamageParams;
	if (bIsRadialDamage)
	{
		DamageParams.bIsRadialDamage = bIsRadialDamage;
		DamageParams.RadialDamageInnerRadius = RadialDamageInnerRadius;
		DamageParams.RadialDamageOuterRadius = RadialDamageOuterRadius;
	}
	return DamageParams;
}
