// Copyright Alien Shores 2025


#include "Game/BlackbirdPlayerStart.h"


// Sets default values
ABlackbirdPlayerStart::ABlackbirdPlayerStart(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
}

ABlackbirdTrack* ABlackbirdPlayerStart::GetTrack() const
{
	return Track;
}
