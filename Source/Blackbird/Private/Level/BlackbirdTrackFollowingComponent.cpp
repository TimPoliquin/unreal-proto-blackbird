// Copyright Alien Shores 2025


#include "Level/BlackbirdTrackFollowingComponent.h"

#include "Level/BlackbirdLevelTrack.h"


// Sets default values for this component's properties
UBlackbirdTrackFollowingComponent::UBlackbirdTrackFollowingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UBlackbirdTrackFollowingComponent::BeginPlay()
{
	Super::BeginPlay();
	MoveAlongTrack();
}

void UBlackbirdTrackFollowingComponent::MoveAlongTrack()
{
	if (Track)
	{
		GetOwner()->SetActorLocation(Track->GetLocationOnTrack(Time / Speed));
		GetOwner()->SetActorRotation(Track->GetRotationOnTrack(Time / Speed));
	}
}


// Called every frame
void UBlackbirdTrackFollowingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (bActive)
	{
		Time += DeltaTime;
		MoveAlongTrack();
	}
}

ABlackbirdLevelTrack* UBlackbirdTrackFollowingComponent::GetTrack()
{
	return Track;
}

void UBlackbirdTrackFollowingComponent::SetTrack(ABlackbirdLevelTrack* InTrack)
{
	Track = InTrack;
}

void UBlackbirdTrackFollowingComponent::Activate(const bool bReset)
{
	Super::Activate(bReset);
	bActive = true;
	if (bReset)
	{
		Time = 0.f;
	}
}

void UBlackbirdTrackFollowingComponent::Deactivate()
{
	Super::Deactivate();
	bActive = false;
}
