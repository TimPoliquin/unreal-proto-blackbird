// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "BlackbirdAbilityAssignment.generated.h"

class UGameplayAbility;

USTRUCT(BlueprintType)
struct FBlackbirdAbilityAssignmentRow
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(Categories="Abilities.State"))
	FGameplayTag AbilityStateTag = FGameplayTag::EmptyTag;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(Categories="InputTag"))
	FGameplayTag InputTag = FGameplayTag::EmptyTag;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayAbility> AbilityClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Level = 1;
};

/**
 * 
 */
UCLASS()
class BLACKBIRD_API UBlackbirdAbilityAssignment : public UDataAsset
{
	GENERATED_BODY()
public:
	TArray<FBlackbirdAbilityAssignmentRow> GetAbilityAssignments() const;
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FBlackbirdAbilityAssignmentRow> AbilityAssignments;
};
