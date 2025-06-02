// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TargetableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UTargetableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BLACKBIRD_API ITargetableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Mark();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Unmark();

	static void Mark(AActor* ToMark);
	static void Unmark(AActor* ToUnmark);
	static bool IsTargetable(const AActor* ToCheck);
};
