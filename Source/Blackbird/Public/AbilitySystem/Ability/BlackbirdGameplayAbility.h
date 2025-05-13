// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "BlackbirdGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class BLACKBIRD_API UBlackbirdGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
	FGameplayTag GetAbilityTag() const;
	FGameplayTag GetAbilityTypeTag() const;

	static bool IsActiveAbilityType(const UGameplayAbility* Ability);
	static bool IsPassiveAbilityType(const UGameplayAbility* Ability);
protected:
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag AbilityTag;
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag AbilityTypeTag;
};
