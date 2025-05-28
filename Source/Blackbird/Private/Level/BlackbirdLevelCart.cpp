// Copyright Alien Shores 2025


#include "Level/BlackbirdLevelCart.h"
#include "Level/BlackbirdTrackFollowingComponent.h"


// Sets default values
ABlackbirdLevelCart::ABlackbirdLevelCart()
{
	PrimaryActorTick.bCanEverTick = false;
	TrackComponent = CreateDefaultSubobject<UBlackbirdTrackFollowingComponent>("TrackComponent");
	TrackComponent->Deactivate();
}

ABlackbirdLevelTrack* ABlackbirdLevelCart::GetTrack() const
{
	return TrackComponent->GetTrack();
}

void ABlackbirdLevelCart::SetTrack(ABlackbirdLevelTrack* LevelTrack)
{
	TrackComponent->SetTrack(LevelTrack);
}

void ABlackbirdLevelCart::StartCart()
{
	TrackComponent->Activate();
}

void ABlackbirdLevelCart::StopCart()
{
	TrackComponent->Deactivate();
}

void ABlackbirdLevelCart::BeginPlay()
{
	Super::BeginPlay();
	if (bAutoStart)
	{
		TrackComponent->Activate();
	}
}

bool ABlackbirdLevelCart::IsAutoStart() const
{
	return bAutoStart;
}

void ABlackbirdLevelCart::SetAutoStart(const bool InAutoStart)
{
	bAutoStart = InAutoStart;
}
