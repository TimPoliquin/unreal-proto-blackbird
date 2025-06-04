// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "BlackbirdTrackEventConfig.generated.h"


UENUM(BlueprintType)
enum class EBlackbirdTrackEventType : uint8
{
	None,
	Instant,
	Duration
};

USTRUCT(BlueprintType)
struct FBlackbirdTrackEventTriggeredPayload
{
	GENERATED_BODY()
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	FName EventName = FName("");
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	FGameplayTag EventTag = FGameplayTag::EmptyTag;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	int32 TriggerCount = 0;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTrackEventTriggeredSignature, AActor*, TriggeringActor, const FBlackbirdTrackEventTriggeredPayload&, Data);
