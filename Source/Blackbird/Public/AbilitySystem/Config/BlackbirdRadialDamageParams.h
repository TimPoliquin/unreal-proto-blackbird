// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "BlackbirdRadialDamageParams.generated.h"

USTRUCT(BlueprintType)
struct FBlackbirdRadialDamageParams
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bIsRadialDamage = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float RadialDamageInnerRadius = 0.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float RadialDamageOuterRadius = 0.f;
	UPROPERTY(BlueprintReadWrite)
	FVector RadialDamageOrigin = FVector::ZeroVector;
};
