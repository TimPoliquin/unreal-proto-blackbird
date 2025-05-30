// Copyright Alien Shores 2025


#include "Track/BlackbirdTrack.h"

#include "Components/SplineComponent.h"
#include "Track/BlackbirdCart.h"
#include "Track/Event/BlackbirdTrackEvent.h"
#include "Track/Event/BlackbirdTrackEventConfig.h"


// Sets default values
ABlackbirdTrack::ABlackbirdTrack()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	TrackSpline = CreateDefaultSubobject<USplineComponent>("TrackSpline");
}

// Called when the game starts or when spawned
void ABlackbirdTrack::BeginPlay()
{
	Super::BeginPlay();
}

ABlackbirdCart* ABlackbirdTrack::SpawnCart()
{
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(GetLocationOnTrack(0.f));
	SpawnTransform.SetRotation(GetRotationOnTrack(0.f).Quaternion());
	ABlackbirdCart* Cart = GetWorld()->SpawnActorDeferred<ABlackbirdCart>(
		TrackCartClass,
		SpawnTransform,
		this,
		nullptr,
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn
	);
	Cart->SetTrack(this);
	Cart->SetAutoStart(bAutoStartCart);
	Cart->FinishSpawning(SpawnTransform);
	return Cart;
}

FVector ABlackbirdTrack::GetLocationOnTrack(const float Progress) const
{
	return TrackSpline->GetLocationAtDistanceAlongSpline(FMath::Lerp(0.f, TrackSpline->GetSplineLength(), Progress), ESplineCoordinateSpace::World);
}

FRotator ABlackbirdTrack::GetRotationOnTrack(const float Progress) const
{
	return TrackSpline->GetRotationAtDistanceAlongSpline(FMath::Lerp(0.f, TrackSpline->GetSplineLength(), Progress), ESplineCoordinateSpace::World);
}

void ABlackbirdTrack::GenerateEvents()
{
	for (int32 EventIdx = TrackEventConfigs.Num(); EventIdx < TrackEvents.Num(); EventIdx++)
	{
		GetWorld()->DestroyActor(TrackEvents[EventIdx]);
	}
	TrackEvents.SetNum(TrackEventConfigs.Num());
	for (int32 EventIdx = 0; EventIdx < TrackEventConfigs.Num(); EventIdx++)
	{
		const FBlackbirdTrackEventConfig& TrackEventConfig = TrackEventConfigs[EventIdx];
		const FVector& SpawnLocation = TrackSpline->GetLocationAtDistanceAlongSpline(TrackEventConfig.StartPosition, ESplineCoordinateSpace::World);
		ABlackbirdTrackEvent* TrackEvent = TrackEvents[EventIdx];
		if (TrackEvent)
		{
			if (TrackEvent->IsA(TrackEventConfig.EventClass))
			{
				TrackEvent->SetActorLocation(SpawnLocation);
			}
			else
			{
				GetWorld()->DestroyActor(TrackEvent);
				TrackEvent = nullptr;
			}
		}
		if (!TrackEvent)
		{
			TrackEvent = GetWorld()->SpawnActor<ABlackbirdTrackEvent>(
				TrackEventConfig.EventClass,
				SpawnLocation,
				FRotator::ZeroRotator,
				FActorSpawnParameters()
			);
			TrackEvent->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
			TrackEvents[EventIdx] = TrackEvent;
		}
		FBlackbirdTrackEventContext Context(
			[this, TrackEventConfig](const float Distance)
			{
				return TrackSpline->GetLocationAtDistanceAlongSpline(TrackEventConfig.StartPosition + Distance, ESplineCoordinateSpace::World);
			},
			[this, TrackEventConfig](const float Distance)
			{
				return TrackSpline->GetRotationAtDistanceAlongSpline(TrackEventConfig.StartPosition + Distance, ESplineCoordinateSpace::World);
			},
			TrackEventConfig
		);
		TrackEvent->GenerateEventKeyFrames(Context);
	}
}
