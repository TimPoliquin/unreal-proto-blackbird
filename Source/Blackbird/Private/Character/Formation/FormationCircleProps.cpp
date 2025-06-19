// Copyright Alien Shores 2025


#include "Character/Formation/FormationCircleProps.h"

void FFormationCircleProps::GetSpawnTransforms(const int32 SpawnCount, TArray<FTransform>& OutSpawnTransforms) const
{
	const FVector& Center = FVector::ZeroVector;

	// Ensure the forward vector is normalized
	const FVector& NormalizedForward = ForwardVector.GetSafeNormal();

	// Generate a perpendicular vector to the forward vector
	const FVector& RightVector = FVector::CrossProduct(NormalizedForward, FVector::UpVector).GetSafeNormal();
	const FVector& UpVector = FVector::CrossProduct(RightVector, NormalizedForward).GetSafeNormal();

	// Calculate positions around the circle
	for (int32 i = 0; i < SpawnCount; ++i)
	{
		FTransform SpawnTransform;
		const float Angle = (2.0f * PI / SpawnCount) * i; // Angle in radians
		FVector Offset = (FMath::Cos(Angle) * RightVector + FMath::Sin(Angle) * UpVector) * Radius;
		SpawnTransform.SetLocation(Center + Offset);
		SpawnTransform.SetRotation(ForwardVector.ToOrientationQuat());
		OutSpawnTransforms.Add(SpawnTransform);
	}
}
