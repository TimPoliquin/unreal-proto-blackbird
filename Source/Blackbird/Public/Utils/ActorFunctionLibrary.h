// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ActorFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class BLACKBIRD_API UActorFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "ActorFunctionLibrary")
	static void DestroyActorHierarchy(AActor* Actor);
};
