// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlackbirdLevelTrack.generated.h"

class ABlackbirdLevelCart;
class USplineComponent;

UCLASS()
class BLACKBIRD_API ABlackbirdLevelTrack : public AActor
{
	GENERATED_BODY()

public:
	ABlackbirdLevelTrack();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Track")
	FVector GetLocationOnTrack(const float Progress) const;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Track")
	FRotator GetRotationOnTrack(const float Progress) const;

	ABlackbirdLevelCart* SpawnCart();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Track")
	TObjectPtr<USplineComponent> TrackSpline;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Track|Cart")
	bool bAutoStartCart = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Track|Cart")
	TSubclassOf<ABlackbirdLevelCart> TrackCartClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Track|Cart")
	TObjectPtr<ABlackbirdLevelCart> TrackCart;
};
