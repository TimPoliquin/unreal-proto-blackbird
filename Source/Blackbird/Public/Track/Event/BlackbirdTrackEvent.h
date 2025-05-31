// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "BlackbirdTrackEventConfig.h"
#include "GameFramework/Actor.h"
#include "BlackbirdTrackEvent.generated.h"

class ABlackbirdTrackEventKeyFrame;

UCLASS(Blueprintable)
class BLACKBIRD_API ABlackbirdTrackEvent : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABlackbirdTrackEvent();
	void GenerateEventKeyFrames(const FBlackbirdTrackEventContext& Context);
	UFUNCTION(BlueprintImplementableEvent)
	void OnTrackEventTriggered(const FBlackbirdTrackEventKeyFrameConfig& KeyFrameConfig, AActor* OtherActor, const int32& TriggerCount);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category="Track|Event")
	TObjectPtr<ABlackbirdTrackEventKeyFrame> StartKeyFrame;
	UPROPERTY(VisibleAnywhere, Category="Track|Event")
	TArray<ABlackbirdTrackEventKeyFrame*> KeyFrames;
	UPROPERTY(VisibleAnywhere, Category="Track|Event")
	TObjectPtr<ABlackbirdTrackEventKeyFrame> EndKeyFrame;
	UPROPERTY(VisibleAnywhere, Category="Track|Event|Config")
	FBlackbirdTrackEventConfig TrackEventConfig;

	void GenerateStartKeyFrameInstance(const FBlackbirdTrackEventContext& Context);
	void GenerateEndKeyFrameInstance(const FBlackbirdTrackEventContext& Context);
	ABlackbirdTrackEventKeyFrame* GenerateKeyFrameInstance(const FBlackbirdTrackEventKeyFrameConfig& KeyFrame, const FBlackbirdTrackEventContext& Context);
	void UpdateKeyFrameInstance(
		ABlackbirdTrackEventKeyFrame* KeyFrameInstance,
		const FBlackbirdTrackEventKeyFrameConfig& KeyFrame,
		const FBlackbirdTrackEventContext& Context
	);
};
