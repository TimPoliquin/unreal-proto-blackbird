// Copyright Alien Shores 2025


#include "AbilitySystem/Energy/MMC_AbilityEnergyCost.h"

#include "Abilities/GameplayAbility.h"
#include "AbilitySystem/Energy/AbilityEnergyCostInterface.h"

float UMMC_AbilityEnergyCost::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const UGameplayAbility* Ability = Spec.GetContext().GetAbilityInstance_NotReplicated();
	if (Ability && Ability->Implements<UAbilityEnergyCostInterface>())
	{
		return -1 * IAbilityEnergyCostInterface::Execute_GetEnergyCost(Ability, Ability->GetAbilityLevel());
	}
	UE_LOG(
		LogTemp,
		Warning,
		TEXT("[%s] Ability uses MMC_AbilityEnergyCost but does not implement EnergyCostInterface: %s"),
		*GetName(),
		Ability ? *Ability->GetName() : TEXT("")
	);
	return 0.0f;
}
