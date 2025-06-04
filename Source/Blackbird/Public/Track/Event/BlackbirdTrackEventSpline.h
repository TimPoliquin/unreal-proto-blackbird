// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "BlackbirdTrackEventBase.h"
#include "BlackbirdTrackEventTriggerComponent.h"
#include "BlackbirdTrackEventSpline.generated.h"

struct FSplinePoint;
class UBlackbirdTrackEventTriggerComponent;
class USplineComponent;

UCLASS()
class BLACKBIRD_API ABlackbirdTrackEventSpline : public ABlackbirdTrackEventBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABlackbirdTrackEventSpline();
	USplineComponent* GetTrack() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Track")
	TObjectPtr<USplineComponent> Track;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Track|Trigger")
	TObjectPtr<UBlackbirdTrackEventTriggerComponent> StartTrigger;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Track|Trigger")
	TObjectPtr<UBlackbirdTrackEventTriggerComponent> EndTrigger;
	UFUNCTION(CallInEditor, Category="Track|Trigger|Generator")
	void AlignTriggersToTrack() const;

private:
	static void InitializeTriggerTransform(UBlackbirdTrackEventTriggerComponent* TriggerComponent, const FSplinePoint& SplinePoint);
};
