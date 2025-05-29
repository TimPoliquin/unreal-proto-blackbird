// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "FormationShapeProps.generated.h"

class ABlackbirdFormation;

UENUM(BlueprintType)
enum class EFormationShape : uint8
{
	Circle
};

/**
 * 
 */
USTRUCT()
struct BLACKBIRD_API FFormationShapeProps
{
	GENERATED_BODY()
	virtual ~FFormationShapeProps() = default;

	virtual void SpawnEnemies(ABlackbirdFormation* Formation)
	{
	};
};
