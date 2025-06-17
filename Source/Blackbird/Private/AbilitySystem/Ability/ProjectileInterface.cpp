// Copyright Alien Shores 2025


#include "AbilitySystem/Ability/ProjectileInterface.h"


UProjectileMovementComponent* IProjectileInterface::GetProjectileMovementComponent(const UObject* Object)
{
	if (IsValid(Object) && Object->Implements<UProjectileInterface>())
	{
		return Execute_GetProjectileMovementComponent(Object);
	}
	return nullptr;
}
