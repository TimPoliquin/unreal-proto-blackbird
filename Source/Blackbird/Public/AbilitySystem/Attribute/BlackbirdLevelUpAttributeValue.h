// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "BlackbirdLevelUpAttributeValue.generated.h"

USTRUCT(BlueprintType)
struct FBlackbirdLevelUpAttributeValue
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attribute", meta=(Categories="Attributes.Primary"))
	FGameplayTag AttributeTag = FGameplayTag::EmptyTag;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attribute")
	int32 Value = 0;
};
