﻿// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TargetingActorInterface.generated.h"

class UPlayerTargetingComponent;
// This class does not need to be modified.
UINTERFACE()
class UTargetingActorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BLACKBIRD_API ITargetingActorInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual UPlayerTargetingComponent* GetTargetingComponent() const = 0;
};
