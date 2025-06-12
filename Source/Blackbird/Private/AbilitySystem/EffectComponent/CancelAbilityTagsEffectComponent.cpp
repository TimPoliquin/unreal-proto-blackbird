// Copyright Alien Shores 2025


#include "AbilitySystem/EffectComponent/CancelAbilityTagsEffectComponent.h"

#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"

void UCancelAbilityTagsEffectComponent::OnGameplayEffectApplied(
	FActiveGameplayEffectsContainer& ActiveGEContainer,
	FGameplayEffectSpec& GESpec,
	FPredictionKey& PredictionKey
) const
{
	Super::OnGameplayEffectApplied(ActiveGEContainer, GESpec, PredictionKey);

	ActiveGEContainer.Owner->CancelAbilities(&WithTags, &WithoutTags, nullptr);
}
