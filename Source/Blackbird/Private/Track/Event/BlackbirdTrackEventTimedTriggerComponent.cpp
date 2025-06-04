// Copyright Alien Shores 2025


#include "Track/Event/BlackbirdTrackEventTimedTriggerComponent.h"

#include "Track/Event/BlackbirdTrackEventTimed.h"


UBlackbirdTrackEventTimedTriggerComponent::UBlackbirdTrackEventTimedTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UBlackbirdTrackEventTimedTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
	if (IsActive())
	{
		Activate(true);
	}
	else
	{
		Deactivate();
	}
}


void UBlackbirdTrackEventTimedTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	ProcessActiveEvents(DeltaTime);
}

void UBlackbirdTrackEventTimedTriggerComponent::FireTrigger(AActor* Actor, const int32 InTriggerCount)
{
	FActiveEvent ActiveEvent;
	ActiveEvent.Actor = Actor;
	ActiveEvent.TriggerCount = InTriggerCount;
	ActiveEvent.CurrentDuration = 0.f;
	ActiveEvents.Add(ActiveEvent);
	Super::FireTrigger(Actor, InTriggerCount);
}

void UBlackbirdTrackEventTimedTriggerComponent::ProcessActiveEvents(float DeltaTime)
{
	if (bActive && ActiveEvents.Num() > 0)
	{
		for (FActiveEvent& Event : ActiveEvents)
		{
			Event.CurrentDuration += DeltaTime;
			if (Event.CurrentDuration > Duration)
			{
				FBlackbirdTrackEventTriggeredPayload Payload;
				Payload.TriggerCount = Event.TriggerCount;
				Payload.EventName = EndEventName;
				Payload.EventTag = EndEventTag;
				OnTrackEventTriggeredDelegate.Broadcast(Event.Actor, Payload);
			}
		}
		ActiveEvents.RemoveAll(
			[this](const FActiveEvent& ActiveEvent)
			{
				return ActiveEvent.CurrentDuration >= Duration;
			}
		);
	}
}

void UBlackbirdTrackEventTimedTriggerComponent::Activate(const bool bReset)
{
	Super::Activate(bReset);
	SetComponentTickEnabled(true);
	bActive = true;
	if (bReset)
	{
		ActiveEvents.Empty();
	}
}

void UBlackbirdTrackEventTimedTriggerComponent::Deactivate()
{
	Super::Deactivate();
	SetComponentTickEnabled(false);
	bActive = false;
	if (ActiveEvents.Num() > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s] Deactivated duration event trigger with some events still active. This can cause memory leaks!"), *GetName())
	}
}
