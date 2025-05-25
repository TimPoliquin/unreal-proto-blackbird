// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "BlackbirdRadialDamageParams.h"
#include "ScalableFloat.h"
#include "BlackbirdDamageConfig.generated.h"

USTRUCT(BlueprintType)
struct FBlackbirdDamageConfig
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FScalableFloat Amount;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float DeathImpulseMagnitude = 6000.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float KnockbackForceMagnitude = 500.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float KnockbackChance = 0.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIsRadialDamage = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(EditCondition="bIsRadialDamage", EditConditionHides))
	float RadialDamageInnerRadius = 0.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(EditCondition="bIsRadialDamage", EditConditionHides))
	float RadialDamageOuterRadius = 0.f;

	FBlackbirdRadialDamageParams GetRadialDamageParams() const;

	int32 GetDamageAtLevel(const int32 AbilityLevel) const
	{
		return Amount.GetValueAtLevel(AbilityLevel);
	}
};
