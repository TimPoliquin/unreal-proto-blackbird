// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/BlackbirdInputConfiguration.h"

const UInputAction* UBlackbirdInputConfiguration::FindAbilityInputActionForTag(
	const FGameplayTag& InputTag,
	bool bLogNotFound
) const
{
	const FBlackbirdInputAction* FoundAction = AbilityInputActions.FindByPredicate([InputTag](const FBlackbirdInputAction& Action)
	{
		return Action.InputTag.IsValid() && Action.InputTag == InputTag;
	});
	if (!FoundAction && bLogNotFound)
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not find InputAction by Tag: [%s]"), *InputTag.ToString());
		return nullptr;
	}
	return FoundAction->InputAction;
}

TArray<FBlackbirdInputAction> UBlackbirdInputConfiguration::GetAbilityInputActions() const
{
	return AbilityInputActions;
}
