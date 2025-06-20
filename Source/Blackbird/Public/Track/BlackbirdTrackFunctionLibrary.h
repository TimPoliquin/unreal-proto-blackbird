﻿// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BlackbirdTrackFunctionLibrary.generated.h"

class USplineComponent;
/**
 * 
 */
UCLASS()
class BLACKBIRD_API UBlackbirdTrackFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Blackbird|Track")
	static FVector GetLocationOnTrack(const USplineComponent* Spline, const float Progress);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Blackbird|Track")
	static FRotator GetRotationOnTrack(const USplineComponent* Spline, const float Progress);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Blackbird|Track")
	static bool HasMoreTrack(const USplineComponent* Spline, const float Progress);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Blackbird|Track")
	static float GetClosestDistanceOnTrack(const USplineComponent* Spline, const FVector& Location);
};
