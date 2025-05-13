// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "GameplayPrediction.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BlackbirdAbilitySystemLibrary.generated.h"

struct FGameplayAbilitySpec;
/**
 * 
 */
UCLASS()
class BLACKBIRD_API UBlackbirdAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	static FPredictionKey GetPredictionKeyFromAbilitySpec(const FGameplayAbilitySpec& AbilitySpec);

};
