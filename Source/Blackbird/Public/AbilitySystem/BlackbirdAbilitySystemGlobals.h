// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "BlackbirdAbilitySystemGlobals.generated.h"

/**
 * 
 */
UCLASS()
class BLACKBIRD_API UBlackbirdAbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()

public:
	virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;
};
