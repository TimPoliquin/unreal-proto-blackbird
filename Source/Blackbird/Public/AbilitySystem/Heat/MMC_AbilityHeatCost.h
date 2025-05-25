// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_AbilityHeatCost.generated.h"

/**
 * 
 */
UCLASS()
class BLACKBIRD_API UMMC_AbilityHeatCost : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
};
