// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "BlackbirdTrackEventBase.h"
#include "BlackbirdTrackEventInstant.generated.h"

class UBlackbirdTrackEventTriggerComponent;

UCLASS()
class BLACKBIRD_API ABlackbirdTrackEventInstant : public ABlackbirdTrackEventBase
{
	GENERATED_BODY()

public:
	ABlackbirdTrackEventInstant();
	virtual EBlackbirdTrackEventType GetTrackEventType() const override { return EBlackbirdTrackEventType::Instant; }

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBlackbirdTrackEventTriggerComponent> Trigger;
};
