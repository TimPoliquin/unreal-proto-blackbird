// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TargetingUtils.generated.h"

/**
 * 
 */
UCLASS()
class BLACKBIRD_API UTargetingUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "TargetingUtils")
	static void FindActorTarget(AActor* Actor, FHitResult& OutHitResult, float TargetingDistance = 10000.f, bool bDebug = false);
	UFUNCTION(
		BlueprintCallable,
		BlueprintPure,
		Category = "TargetingUtils",
		meta=( DefaultToSelf="Instigator" )
	)
	static FVector CalculateInterceptVector(const AActor* Instigator, const AActor* Target, const float TimeToIntercept);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "TargetingUtils")
	static float CalculateAngleBetweenVectors(const FVector& VectorA, const FVector& VectorB);
};
