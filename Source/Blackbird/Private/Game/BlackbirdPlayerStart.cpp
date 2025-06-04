// Copyright Alien Shores 2025


#include "Game/BlackbirdPlayerStart.h"

#include "Track/Event/BlackbirdTrackEventSpline.h"


// Sets default values
ABlackbirdPlayerStart::ABlackbirdPlayerStart(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
}

USplineComponent* ABlackbirdPlayerStart::GetTrack() const
{
	return Track->GetTrack();
}
