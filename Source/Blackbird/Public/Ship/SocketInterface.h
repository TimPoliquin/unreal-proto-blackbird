// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SocketInterface.generated.h"

struct FGameplayTag;
// This class does not need to be modified.
UINTERFACE()
class USocketInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BLACKBIRD_API ISocketInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual FVector GetSocketLocation(const FGameplayTag& SocketTag) const = 0;
	virtual FRotator GetSocketRotation(FGameplayTag SocketTag) const = 0;
};
