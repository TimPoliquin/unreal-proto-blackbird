// Copyright Alien Shores 2025


#include "AbilitySystem/BlackbirdAbilitySystemGlobals.h"

#include "AbilitySystem/BlackbirdGameplayEffectContext.h"

FGameplayEffectContext* UBlackbirdAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FBlackbirdGameplayEffectContext();
}
