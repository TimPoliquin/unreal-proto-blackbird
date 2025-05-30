// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "BlackbirdTrackEventConfig.generated.h"

class ABlackbirdTrackEvent;

USTRUCT(BlueprintType)
struct FBlackbirdTrackEventKeyFrameConfig
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName Name = FName();
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Index = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="Track.Event"))
	FGameplayTag KeyFrameTag = FGameplayTag::EmptyTag;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bOneTimeTrigger = true;
};

USTRUCT(BlueprintType)
struct FBlackbirdTrackEventConfig
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float StartPosition = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Length = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bOneTimeTrigger = true;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ABlackbirdTrackEvent> EventClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FBlackbirdTrackEventKeyFrameConfig> Keys;
};

struct FBlackbirdTrackEventContext
{
	TFunction<FVector(const float)> GetEventKeyFrameLocation;
	TFunction<FRotator(const float)> GetEventKeyFrameRotation;
	const FBlackbirdTrackEventConfig& TrackEventConfig;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(
	FOnTrackEventKeyFrameTriggeredSignature,
	const FBlackbirdTrackEventKeyFrameConfig&,
	KeyFrameConfig,
	AActor*,
	OtherActor,
	const int32&,
	TriggerCount
);
