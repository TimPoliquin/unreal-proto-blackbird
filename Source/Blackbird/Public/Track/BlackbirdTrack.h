// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlackbirdTrack.generated.h"

class ABlackbirdTrackEvent;
struct FBlackbirdTrackEventConfig;
class ABlackbirdCart;
class USplineComponent;

UCLASS()
class BLACKBIRD_API ABlackbirdTrack : public AActor
{
	GENERATED_BODY()

public:
	ABlackbirdTrack();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Track")
	FVector GetLocationOnTrack(const float Progress) const;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Track")
	FRotator GetRotationOnTrack(const float Progress) const;

	UFUNCTION(CallInEditor, Category="Track|Events")
	void GenerateEvents();

	ABlackbirdCart* SpawnCart();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Track")
	TObjectPtr<USplineComponent> TrackSpline;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Track|Cart")
	bool bAutoStartCart = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Track|Cart")
	TSubclassOf<ABlackbirdCart> TrackCartClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Track|Cart")
	TObjectPtr<ABlackbirdCart> TrackCart;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Track|Events")
	TArray<FBlackbirdTrackEventConfig> TrackEventConfigs;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Track|Events")
	TArray<ABlackbirdTrackEvent*> TrackEvents;
};
