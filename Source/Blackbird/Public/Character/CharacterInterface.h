// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CharacterInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UCharacterInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BLACKBIRD_API ICharacterInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void SetFacingDirection(const FVector& Direction) = 0;
};
