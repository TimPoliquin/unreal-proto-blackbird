// Copyright Alien Shores 2025


#include "Level/BlackbirdLevelTrack.h"
#include "Components/SplineComponent.h"
#include "Level/BlackbirdLevelCart.h"


// Sets default values
ABlackbirdLevelTrack::ABlackbirdLevelTrack()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	TrackSpline = CreateDefaultSubobject<USplineComponent>("TrackSpline");
}

// Called when the game starts or when spawned
void ABlackbirdLevelTrack::BeginPlay()
{
	Super::BeginPlay();
}

ABlackbirdLevelCart* ABlackbirdLevelTrack::SpawnCart()
{
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(GetLocationOnTrack(0.f));
	SpawnTransform.SetRotation(GetRotationOnTrack(0.f).Quaternion());
	ABlackbirdLevelCart* Cart = GetWorld()->SpawnActorDeferred<ABlackbirdLevelCart>(
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

FVector ABlackbirdLevelTrack::GetLocationOnTrack(const float Progress) const
{
	return TrackSpline->GetLocationAtDistanceAlongSpline(FMath::Lerp(0.f, TrackSpline->GetSplineLength(), Progress), ESplineCoordinateSpace::World);
}

FRotator ABlackbirdLevelTrack::GetRotationOnTrack(const float Progress) const
{
	return TrackSpline->GetRotationAtDistanceAlongSpline(FMath::Lerp(0.f, TrackSpline->GetSplineLength(), Progress), ESplineCoordinateSpace::World);
}
