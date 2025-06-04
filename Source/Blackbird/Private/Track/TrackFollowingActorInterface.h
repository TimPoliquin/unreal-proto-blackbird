// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TrackFollowingActorInterface.generated.h"

class UBlackbirdTrackFollowingComponent;
// This class does not need to be modified.
UINTERFACE()
class UTrackFollowingActorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BLACKBIRD_API ITrackFollowingActorInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual UBlackbirdTrackFollowingComponent* GetTrackFollowingComponent() const = 0;
};
