// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "UObject/Object.h"
#include "MMC_AbilityEnergyCost.generated.h"

/**
 * 
 */
UCLASS()
class BLACKBIRD_API UMMC_AbilityEnergyCost : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
};
