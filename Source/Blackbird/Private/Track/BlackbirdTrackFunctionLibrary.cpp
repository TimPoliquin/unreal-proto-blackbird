// Copyright Alien Shores 2025


#include "Track/BlackbirdTrackFunctionLibrary.h"

#include "Components/SplineComponent.h"
#include "Track/BlackbirdCart.h"

FVector UBlackbirdTrackFunctionLibrary::GetLocationOnTrack(const USplineComponent* Spline, const float Progress)
{
	return Spline->GetLocationAtDistanceAlongSpline(Progress, ESplineCoordinateSpace::World);
}

FRotator UBlackbirdTrackFunctionLibrary::GetRotationOnTrack(const USplineComponent* Spline, const float Progress)
{
	return Spline->GetRotationAtDistanceAlongSpline(Progress, ESplineCoordinateSpace::World);
}

bool UBlackbirdTrackFunctionLibrary::HasMoreTrack(const USplineComponent* Spline, const float Progress)
{
	return Spline->GetSplineLength() > Progress;
}

float UBlackbirdTrackFunctionLibrary::GetClosestDistanceOnTrack(const USplineComponent* Spline, const FVector& Location)
{
	return Spline->GetDistanceAlongSplineAtLocation(Location, ESplineCoordinateSpace::World);
}

ABlackbirdCart* UBlackbirdTrackFunctionLibrary::SpawnCart(USplineComponent* Track, const TSubclassOf<ABlackbirdCart> CartClass, const bool bAutoStart = true)
{
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(GetLocationOnTrack(Track, 0.f));
	SpawnTransform.SetRotation(GetRotationOnTrack(Track, 0.f).Quaternion());
	ABlackbirdCart* Cart = Track->GetWorld()->SpawnActorDeferred<ABlackbirdCart>(
		CartClass,
		SpawnTransform,
		Track->GetOwner(),
		nullptr,
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn
	);
	Cart->SetTrack(Track);
	Cart->SetAutoStart(bAutoStart);
	Cart->FinishSpawning(SpawnTransform);
	return Cart;
}
