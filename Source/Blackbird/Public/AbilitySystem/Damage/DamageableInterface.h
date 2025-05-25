// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DamageableInterface.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnDamageSignature, float /* Damage Amount */);

// This class does not need to be modified.
UINTERFACE()
class UDamageableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BLACKBIRD_API IDamageableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual FOnDamageSignature& GetOnDamageDelegate() = 0;
};
