// Copyright Alien Shores 2025


#include "AbilitySystem/BlackbirdAbilitySystemLibrary.h"

#include "GameplayAbilitySpec.h"
#include "Abilities/GameplayAbility.h"

FPredictionKey UBlackbirdAbilitySystemLibrary::GetPredictionKeyFromAbilitySpec(const FGameplayAbilitySpec& AbilitySpec)
{
	if (TArray<UGameplayAbility*> Instances = AbilitySpec.GetAbilityInstances(); Instances.Num() > 0)
	{
		const FGameplayAbilityActivationInfo& ActivationInfo = Instances.Last()->GetCurrentActivationInfoRef();
		return ActivationInfo.GetActivationPredictionKey();
	}
	return FPredictionKey();
}
