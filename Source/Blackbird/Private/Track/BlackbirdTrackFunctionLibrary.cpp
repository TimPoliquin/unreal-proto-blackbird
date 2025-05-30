// Copyright Alien Shores 2025


#include "Track/BlackbirdTrackFunctionLibrary.h"

#include "Components/SplineComponent.h"

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
