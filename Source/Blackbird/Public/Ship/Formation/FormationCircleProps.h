// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "FormationShapeProps.h"
#include "UObject/Object.h"
#include "FormationCircleProps.generated.h"

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

	virtual void SpawnEnemies(ABlackbirdFormation* Formation) override;

	static TArray<FVector> GetPositionsInACircle(const FVector& Center, const FVector& ForwardVector, float Radius, int32 NumPoints);
};
