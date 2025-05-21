// Copyright Alien Shores 2025


#include "AbilitySystem/BlackbirdAbilitySystemComponent.h"

#include "AbilitySystem/Ability/BlackbirdAbilityAssignment.h"
#include "AbilitySystem/BlackbirdAbilitySystemLibrary.h"
#include "AbilitySystem/Ability/BlackbirdGameplayAbility.h"

void UBlackbirdAbilitySystemComponent::ForEachAbility(const FForEachAbility& ForEachAbilityDelegate)
{
	// This locks the ability system abilities for the scope of this function call.
	FScopedAbilityListLock ActiveScopeLock(*this);
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (!ForEachAbilityDelegate.ExecuteIfBound(AbilitySpec))
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to execute delegate in [%hs]"), __FUNCTION__);
		}
	}
}

void UBlackbirdAbilitySystemComponent::AddAbilities(TArray<FBlackbirdAbilityAssignmentRow> AbilityAssignments)
{
	if (!GetOwner()->HasAuthority())
	{
		return;
	}
	for (const FBlackbirdAbilityAssignmentRow& AbilityAssignment : AbilityAssignments)
	{
		AddAbility(AbilityAssignment);
	}
	bAbilitiesGiven = true;
	OnAbilitiesGivenDelegate.Broadcast();
}

void UBlackbirdAbilitySystemComponent::AbilityInputTagPressed(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid())
	{
		return;
	}
	FForEachAbility ForEachAbilityDelegate;
	ForEachAbilityDelegate.BindLambda(
		[this, InputTag](FGameplayAbilitySpec& AbilitySpec)
		{
			if (AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag))
			{
				AbilitySpecInputPressed(AbilitySpec);
				if (AbilitySpec.IsActive())
				{
					InvokeReplicatedEvent(
						EAbilityGenericReplicatedEvent::InputPressed,
						AbilitySpec.Handle,
						UBlackbirdAbilitySystemLibrary::GetPredictionKeyFromAbilitySpec(AbilitySpec)
					);
				}
			}
		}
	);
	ForEachAbility(ForEachAbilityDelegate);
}

void UBlackbirdAbilitySystemComponent::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (!InputTag.IsValid())
	{
		return;
	}
	FForEachAbility Delegate;
	Delegate.BindLambda(
		[this, InputTag](FGameplayAbilitySpec& AbilitySpec)
		{
			if (AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag))
			{
				AbilitySpecInputPressed(AbilitySpec);
				if (!AbilitySpec.IsActive())
				{
					TryActivateAbility(AbilitySpec.Handle);
				}
			}
		}
	);
	ForEachAbility(Delegate);
}

void UBlackbirdAbilitySystemComponent::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (!InputTag.IsValid())
	{
		return;
	}
	FForEachAbility Delegate;

	Delegate.BindLambda(
		[this, InputTag](FGameplayAbilitySpec& AbilitySpec)
		{
			if (AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag) && AbilitySpec.IsActive())
			{
				AbilitySpecInputReleased(AbilitySpec);
				InvokeReplicatedEvent(
					EAbilityGenericReplicatedEvent::InputReleased,
					AbilitySpec.Handle,
					UBlackbirdAbilitySystemLibrary::GetPredictionKeyFromAbilitySpec(AbilitySpec)
				);
			}
		}
	);
	ForEachAbility(Delegate);
}

void UBlackbirdAbilitySystemComponent::OnRep_ActivateAbilities()
{
	Super::OnRep_ActivateAbilities();
	if (!bAbilitiesGiven)
	{
		bAbilitiesGiven = true;
		OnAbilitiesGivenDelegate.Broadcast();
	}
}

void UBlackbirdAbilitySystemComponent::AddAbility(const FBlackbirdAbilityAssignmentRow& AbilityAssignmentRow)
{
	FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(
		AbilityAssignmentRow.AbilityClass,
		AbilityAssignmentRow.Level
	);
	AbilitySpec.GetDynamicSpecSourceTags().AddTag(AbilityAssignmentRow.AbilityStateTag);
	AbilitySpec.GetDynamicSpecSourceTags().AddTag(AbilityAssignmentRow.InputTag);
	UE_LOG(
		LogTemp,
		Warning,
		TEXT("[%s] Adding ability: %s"),
		GetOwner()->HasAuthority() ? TEXT("Server") : TEXT("Client"),
		*AbilityAssignmentRow.AbilityClass->GetName()
	);
	if (UBlackbirdGameplayAbility::IsPassiveAbilityType(AbilitySpec.Ability))
	{
		GiveAbilityAndActivateOnce(AbilitySpec);
	}
	else
	{
		GiveAbility(AbilitySpec);
	}
}
