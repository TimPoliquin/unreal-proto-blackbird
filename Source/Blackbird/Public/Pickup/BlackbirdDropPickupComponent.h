// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BlackbirdDropPickupComponent.generated.h"


class ABlackbirdPickup;

USTRUCT(BlueprintType)
struct FBlackbirdDropDefinition
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ABlackbirdPickup> DropClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = 0.f, ClampMax = 1.f, UIMin = 0.f, UIMax = 1.f))
	float DropChance = 1.f;

	bool RollForDrop() const;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BLACKBIRD_API UBlackbirdDropPickupComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBlackbirdDropPickupComponent();
	UFUNCTION(BlueprintCallable)
	TArray<ABlackbirdPickup*> Drop() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Drops")
	TArray<FBlackbirdDropDefinition> DropClasses;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Drops", meta = (ClampMin = 0, UIMin = 0))
	int32 NumDrops = 1;
};
