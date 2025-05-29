// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "FormationShapeProps.generated.h"

class UBlackbirdFormationComponent;

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

	virtual void GetSpawnTransforms(const int32 SpawnCount, TArray<FTransform>& OutSpawnTransforms) const
	{
	};
};
