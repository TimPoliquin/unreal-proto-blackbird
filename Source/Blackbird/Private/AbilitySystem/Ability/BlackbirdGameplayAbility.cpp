// Copyright Alien Shores 2025


#include "AbilitySystem/Ability/BlackbirdGameplayAbility.h"

#include "AbilitySystem/Ability/BlackbirdAbilitySystemTags.h"

FGameplayTag UBlackbirdGameplayAbility::GetAbilityTag() const
{
	return AbilityTag;
}

FGameplayTag UBlackbirdGameplayAbility::GetAbilityTypeTag() const
{
	return AbilityTypeTag;
}

bool UBlackbirdGameplayAbility::IsActiveAbilityType(const UGameplayAbility* Ability)
{
	if (const UBlackbirdGameplayAbility* BlackbirdAbility = Cast<UBlackbirdGameplayAbility>(Ability))
	{
		return BlackbirdAbility->GetAbilityTypeTag().MatchesTagExact(FBlackbirdAbilitySystemTags::Get().Abilities_Type_Active);
	}
	return false;
}

bool UBlackbirdGameplayAbility::IsPassiveAbilityType(const UGameplayAbility* Ability)
{
	if (const UBlackbirdGameplayAbility* BlackbirdAbility = Cast<UBlackbirdGameplayAbility>(Ability))
	{
		return BlackbirdAbility->GetAbilityTypeTag().MatchesTagExact(FBlackbirdAbilitySystemTags::Get().Abilities_Type_Passive);
	}
	return false;
}
