// Copyright Alien Shores 2025


#include "Track/Event/BlackbirdTrackEventInstant.h"

#include "Track/Event/BlackbirdTrackEventTriggerComponent.h"


// Sets default values
ABlackbirdTrackEventInstant::ABlackbirdTrackEventInstant()
{
	PrimaryActorTick.bCanEverTick = false;
	Trigger = CreateDefaultSubobject<UBlackbirdTrackEventTriggerComponent>(TEXT("Trigger"));
	Trigger->SetupAttachment(GetRootComponent());
}
