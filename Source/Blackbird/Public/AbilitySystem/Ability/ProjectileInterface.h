// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ProjectileInterface.generated.h"

class UProjectileMovementComponent;
// This class does not need to be modified.
UINTERFACE()
class UProjectileInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BLACKBIRD_API IProjectileInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	UProjectileMovementComponent* GetProjectileMovementComponent() const;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Repel(AActor* NewOwner, const FHitResult& NewTarget, const float RepelAngle = 90.f, const float BaseDamageMultiplier = 1.f);
	
	static UProjectileMovementComponent* GetProjectileMovementComponent(const UObject* Object);
};
