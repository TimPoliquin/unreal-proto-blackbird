// Copyright Alien Shores 2025


#include "Track/BlackbirdCart.h"
#include "Track/BlackbirdTrackFollowingComponent.h"


// Sets default values
ABlackbirdCart::ABlackbirdCart()
{
	PrimaryActorTick.bCanEverTick = false;
	TrackComponent = CreateDefaultSubobject<UBlackbirdTrackFollowingComponent>("TrackComponent");
	TrackComponent->Deactivate();
}

USplineComponent* ABlackbirdCart::GetTrack() const
{
	return TrackComponent->GetTrack();
}

void ABlackbirdCart::SetTrack(USplineComponent* Track)
{
	TrackComponent->SetTrack(Track);
}

void ABlackbirdCart::StartCart()
{
	TrackComponent->Activate();
}

void ABlackbirdCart::StopCart()
{
	TrackComponent->Deactivate();
}

void ABlackbirdCart::SwitchToTrack(USplineComponent* NewTrack)
{
	TrackComponent->SwitchToTrack(NewTrack);
}

void ABlackbirdCart::ChangeSpeed(const float NewSpeed)
{
	TrackComponent->ChangeSpeed(NewSpeed);
}

void ABlackbirdCart::BeginPlay()
{
	Super::BeginPlay();
	if (bAutoStart)
	{
		TrackComponent->Activate();
	}
}

bool ABlackbirdCart::IsAutoStart() const
{
	return bAutoStart;
}

void ABlackbirdCart::SetAutoStart(const bool InAutoStart)
{
	bAutoStart = InAutoStart;
}
