// Copyright Alien Shores 2025


#include "Track/Event/BlackbirdTrackEventSpline.h"

#include "Components/SplineComponent.h"
#include "Track/Event/BlackbirdTrackEventTriggerComponent.h"


// Sets default values
ABlackbirdTrackEventSpline::ABlackbirdTrackEventSpline()
{
	PrimaryActorTick.bCanEverTick = false;
	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	Track = CreateDefaultSubobject<USplineComponent>(TEXT("Track"));
	Track->SetupAttachment(GetRootComponent());
	StartTrigger = CreateDefaultSubobject<UBlackbirdTrackEventTriggerComponent>(TEXT("Start Trigger"));
	StartTrigger->SetupAttachment(Track);
	EndTrigger = CreateDefaultSubobject<UBlackbirdTrackEventTriggerComponent>(TEXT("End Trigger"));
	EndTrigger->SetupAttachment(Track);
	AlignTriggersToTrack();
}

USplineComponent* ABlackbirdTrackEventSpline::GetTrack() const
{
	return Track;
}

void ABlackbirdTrackEventSpline::AlignTriggersToTrack() const
{
	TArray<UBlackbirdTrackEventTriggerComponent*> TriggerComponents;
	GetComponents<UBlackbirdTrackEventTriggerComponent>(TriggerComponents);
	StartTrigger->SetSplinePointIndex(0);
	EndTrigger->SetSplinePointIndex(Track->GetNumberOfSplinePoints() - 1);
	for (UBlackbirdTrackEventTriggerComponent* TriggerComponent : TriggerComponents)
	{
		if (TriggerComponent->GetSplinePointIndex() >= 0 && TriggerComponent->GetSplinePointIndex() < Track->GetNumberOfSplinePoints())
		{
			InitializeTriggerTransform(
				TriggerComponent,
				Track->GetSplinePointAt(TriggerComponent->GetSplinePointIndex(), ESplineCoordinateSpace::Local)
			);
		}
		else
		{
			UE_LOG(
				LogTemp,
				Error,
				TEXT("[%s] Trigger component [%s] spline point index [%d] out of range [%d-%d]."),
				*GetName(),
				*TriggerComponent->GetName(),
				TriggerComponent->GetSplinePointIndex(),
				0,
				Track->GetNumberOfSplinePoints() - 1
			);
		}
	}
}

void ABlackbirdTrackEventSpline::BeginPlay()
{
	Super::BeginPlay();
	AlignTriggersToTrack();
}

void ABlackbirdTrackEventSpline::InitializeTriggerTransform(UBlackbirdTrackEventTriggerComponent* TriggerComponent, const FSplinePoint& SplinePoint)
{
	if (TriggerComponent)
	{
		TriggerComponent->SetRelativeLocation(SplinePoint.Position);
		TriggerComponent->SetRelativeRotation(SplinePoint.Rotation);
	}
}
