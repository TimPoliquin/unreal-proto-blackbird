// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "BlackbirdAbilitySystemComponent.generated.h"

struct FBlackbirdAbilityAssignmentRow;
DECLARE_DELEGATE_OneParam(FForEachAbility, FGameplayAbilitySpec&);
DECLARE_MULTICAST_DELEGATE(FAbilitiesGivenSignature);

/**
 * 
 */
UCLASS()
class BLACKBIRD_API UBlackbirdAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override{}
	virtual void OnGameplayTaskDeactivated(UGameplayTask& Task) override{}

	void ForEachAbility(const FForEachAbility& ForEachAbilityDelegate);
	void AddAbilities(TArray<FBlackbirdAbilityAssignmentRow> AbilityAssignments);
	void AbilityInputTagPressed(const FGameplayTag& InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	
	virtual void OnRep_ActivateAbilities() override;
	FAbilitiesGivenSignature OnAbilitiesGivenDelegate;

protected:
	void AddAbility(const FBlackbirdAbilityAssignmentRow& AbilityAssignmentRow);
	
private:
	bool bAbilitiesGiven = false;
	
};
