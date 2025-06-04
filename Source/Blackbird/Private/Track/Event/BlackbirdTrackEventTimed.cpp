// Copyright Alien Shores 2025


#include "Track/Event/BlackbirdTrackEventTimed.h"

#include "Track/Event/BlackbirdTrackEventTimedTriggerComponent.h"


ABlackbirdTrackEventTimed::ABlackbirdTrackEventTimed()
{
	PrimaryActorTick.bCanEverTick = true;
	Trigger = CreateDefaultSubobject<UBlackbirdTrackEventTimedTriggerComponent>(TEXT("Timed Trigger"));
	Trigger->SetupAttachment(GetRootComponent());
}
