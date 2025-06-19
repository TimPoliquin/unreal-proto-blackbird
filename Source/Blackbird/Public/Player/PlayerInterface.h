// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "UObject/Interface.h"
#include "PlayerInterface.generated.h"

class ABlackbirdPlayerCamera;
// This class does not need to be modified.
UINTERFACE()
class UPlayerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BLACKBIRD_API IPlayerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual UCameraComponent* GetCameraComponent() const = 0;

	static UCameraComponent* GetCameraComponent(AActor* Actor);
};
