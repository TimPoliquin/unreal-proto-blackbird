// Copyright Alien Shores 2025


#include "Track/Event/BlackbirdTrackEventBase.h"

#include "Track/Event/BlackbirdTrackEventTriggerComponent.h"


ABlackbirdTrackEventBase::ABlackbirdTrackEventBase()
{
	PrimaryActorTick.bCanEverTick = false;
}


void ABlackbirdTrackEventBase::BeginPlay()
{
	Super::BeginPlay();
}

void ABlackbirdTrackEventBase::SetupTriggers()
{
	TArray<UBlackbirdTrackEventTriggerComponent*> TriggerComponents;
	GetComponents<UBlackbirdTrackEventTriggerComponent>(TriggerComponents);
	for (UBlackbirdTrackEventTriggerComponent* TriggerComponent : TriggerComponents)
	{
		TriggerComponent->OnTrackEventTriggeredDelegate.AddDynamic(this, &ABlackbirdTrackEventBase::OnTrackEventTriggered);
	}
}

void ABlackbirdTrackEventBase::OnTrackEventTriggered(AActor* TriggeringActor, const FBlackbirdTrackEventTriggeredPayload& Data)
{
	HandleTrackEvent(TriggeringActor, Data);
	OnTrackEventTriggeredDelegate.Broadcast(TriggeringActor, Data);
}
