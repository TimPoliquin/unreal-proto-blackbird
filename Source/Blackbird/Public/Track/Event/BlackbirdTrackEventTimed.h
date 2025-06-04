// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "BlackbirdTrackEventBase.h"
#include "BlackbirdTrackEventTimed.generated.h"

class UBlackbirdTrackEventTimedTriggerComponent;
class UBlackbirdTrackEventTriggerComponent;


UCLASS()
class BLACKBIRD_API ABlackbirdTrackEventTimed : public ABlackbirdTrackEventBase
{
	GENERATED_BODY()

public:
	ABlackbirdTrackEventTimed();
	virtual EBlackbirdTrackEventType GetTrackEventType() const override { return EBlackbirdTrackEventType::Duration; };

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBlackbirdTrackEventTimedTriggerComponent> Trigger;
};
