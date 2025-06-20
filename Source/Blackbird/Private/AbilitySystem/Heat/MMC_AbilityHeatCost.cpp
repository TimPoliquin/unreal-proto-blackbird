﻿// Copyright Alien Shores 2025


#include "AbilitySystem/Heat/MMC_AbilityHeatCost.h"

#include "Abilities/GameplayAbility.h"
#include "AbilitySystem/Heat/AbilityHeatCostInterface.h"

float UMMC_AbilityHeatCost::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const UGameplayAbility* Ability = Spec.GetContext().GetAbilityInstance_NotReplicated();
	if (Ability && Ability->Implements<UAbilityHeatCostInterface>())
	{
		return -1 * IAbilityHeatCostInterface::Execute_GetHeatCost(Ability, Ability->GetAbilityLevel());
	}
	UE_LOG(
		LogTemp,
		Warning,
		TEXT("[%s] Ability uses MMC_AbilityHeatCost but does not implement HeatCostInterface: %s"),
		*GetName(),
		Ability ? *Ability->GetName() : TEXT("")
	);
	return 0.0f;
}
