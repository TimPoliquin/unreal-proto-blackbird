// Copyright Alien Shores 2025


#include "BlackbirdSquadron.h"

#include "Components/SplineComponent.h"
#include "Ship/BlackbirdEnemyShip.h"
#include "Ship/Formation/BlackbirdFormationComponent.h"
#include "Track/BlackbirdTrackFollowingComponent.h"


// Sets default values
ABlackbirdSquadron::ABlackbirdSquadron()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	FormationComponent = CreateDefaultSubobject<UBlackbirdFormationComponent>(TEXT("Formation Component"));
}

void ABlackbirdSquadron::BeginPlay()
{
	Super::BeginPlay();
	if (Track)
	{
		SetTrackOnChildren();
	}
}

void ABlackbirdSquadron::SetTrack(USplineComponent* InTrack)
{
	Track = InTrack;
	SetActorLocation(Track->GetWorldLocationAtSplinePoint(0));
	SetActorRotation(Track->GetWorldRotationAtDistanceAlongSpline(0));
	SetTrackOnChildren();
}

void ABlackbirdSquadron::Spawn() const
{
	FormationComponent->SpawnEnemies();
	SetTrackOnChildren();
}

void ABlackbirdSquadron::SetTrackOnChildren() const
{
	for (const ABlackbirdEnemyShip* Ship : FormationComponent->GetEnemies())
	{
		Ship->GetTrackFollowingComponent()->SetTrack(Track);
		if (Track != nullptr)
		{
			Ship->GetTrackFollowingComponent()->Activate(true);
		}
	}
}
