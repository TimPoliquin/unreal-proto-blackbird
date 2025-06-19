// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "FormationShapeProps.h"
#include "FormationCircleProps.generated.h"

class UBlackbirdFormationComponent;

/**
 * 
 */
USTRUCT(BlueprintType)
struct FFormationCircleProps : public FFormationShapeProps
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Radius = 20.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector ForwardVector = FVector::ForwardVector;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Rotation = 0.f;

	virtual void GetSpawnTransforms(const int32 SpawnCount, TArray<FTransform>& OutSpawnTransforms) const override;
};
