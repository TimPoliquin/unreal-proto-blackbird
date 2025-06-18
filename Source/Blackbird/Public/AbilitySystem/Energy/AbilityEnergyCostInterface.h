// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AbilityEnergyCostInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UAbilityEnergyCostInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BLACKBIRD_API IAbilityEnergyCostInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	float GetEnergyCost(const float InLevel = 1.f) const;
};
