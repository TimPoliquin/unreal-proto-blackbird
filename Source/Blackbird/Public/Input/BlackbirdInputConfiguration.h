// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "BlackbirdInputConfiguration.generated.h"


class UInputAction;

USTRUCT(BlueprintType)
struct FBlackbirdInputAction
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	const UInputAction* InputAction = nullptr;
	UPROPERTY(EditDefaultsOnly, meta=(Categories="InputTag"))
	FGameplayTag InputTag = FGameplayTag::EmptyTag;
};

/**
 * 
 */
UCLASS()
class BLACKBIRD_API UBlackbirdInputConfiguration : public UDataAsset
{
	GENERATED_BODY()

public:
	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = false) const;
	TArray<FBlackbirdInputAction> GetAbilityInputActions() const;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input")
	TArray<FBlackbirdInputAction> AbilityInputActions;
};
