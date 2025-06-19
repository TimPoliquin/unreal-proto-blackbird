// Copyright Alien Shores 2025


#include "Player/PlayerInterface.h"

#include "Camera/CameraComponent.h"
#include "Player/BlackbirdPlayerCamera.h"


// Add default functionality here for any IPlayerInterface functions that are not pure virtual.
UCameraComponent* IPlayerInterface::GetCameraComponent(AActor* Actor)
{
	if (IsValid(Actor))
	{
		if (const IPlayerInterface* PlayerInterface = Cast<IPlayerInterface>(Actor))
		{
			return PlayerInterface->GetCameraComponent();
		}
		return Actor->FindComponentByClass<UCameraComponent>();
	}
	return nullptr;
}
