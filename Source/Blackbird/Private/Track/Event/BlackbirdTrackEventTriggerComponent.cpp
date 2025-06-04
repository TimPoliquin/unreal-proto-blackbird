// Copyright Alien Shores 2025


#include "Track/Event/BlackbirdTrackEventTriggerComponent.h"

#include "Components/BoxComponent.h"


UBlackbirdTrackEventTriggerComponent::UBlackbirdTrackEventTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UBlackbirdTrackEventTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
	TriggerBox = NewObject<UBoxComponent>(this, UBoxComponent::StaticClass(), TEXT("Event Trigger Box"));
	GetOwner()->AddInstanceComponent(TriggerBox);
	GetOwner()->AddOwnedComponent(TriggerBox);
	TriggerBox->RegisterComponent();
	TriggerBox->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	TriggerBox->SetBoxExtent(FVector(2, 100, 100));
	TriggerBox->SetGenerateOverlapEvents(true);
	TriggerBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	TriggerBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	TriggerBox->SetHiddenInGame(false);
	TriggerBox->SetLineThickness(1.f);
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &UBlackbirdTrackEventTriggerComponent::OnTriggerBeginOverlap);
}

void UBlackbirdTrackEventTriggerComponent::FireTrigger(AActor* Actor, const int32 InTriggerCount)
{
	FBlackbirdTrackEventTriggeredPayload Payload;
	Payload.EventName = EventName;
	Payload.EventTag = EventTag;
	Payload.TriggerCount = InTriggerCount;
	OnTrackEventTriggeredDelegate.Broadcast(Actor, Payload);
}

bool UBlackbirdTrackEventTriggerComponent::CanTrigger() const
{
	return MaxTriggerCount > 0
		       ? TriggerCount < MaxTriggerCount
		       : true;
}

int32 UBlackbirdTrackEventTriggerComponent::GetSplinePointIndex() const
{
	return SplinePointIndex;
}

void UBlackbirdTrackEventTriggerComponent::SetSplinePointIndex(int32 InSplinePointIndex)
{
	SplinePointIndex = InSplinePointIndex;
}

bool UBlackbirdTrackEventTriggerComponent::IsTriggeringActor(const AActor* Actor) const
{
	if (IsValid(Actor))
	{
		bool bIsTriggering = true;
		for (const FName& TriggerActorTag : TriggerActorTags)
		{
			bIsTriggering &= Actor->ActorHasTag(TriggerActorTag);
		}
		return bIsTriggering;
	}
	return false;
}

int32 UBlackbirdTrackEventTriggerComponent::GetTriggerCount() const
{
	return TriggerCount;
}

void UBlackbirdTrackEventTriggerComponent::OnTriggerBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool BFromSweep,
	const FHitResult& SweepResult
)
{
	UE_LOG(LogTemp, Warning, TEXT("[%s] Overlapping with [%s]"), *GetName(), *OtherActor->GetName());
	if (CanTrigger() && IsTriggeringActor(OtherActor))
	{
		TriggerCount++;
		FireTrigger(OtherActor, TriggerCount);
	}
}
