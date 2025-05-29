// Copyright Alien Shores 2025


#include "Ship/Formation/FormationCircleProps.h"

#include "Ship/BlackbirdEnemyShip.h"
#include "Ship/Formation/BlackbirdFormation.h"

void FFormationCircleProps::SpawnEnemies(ABlackbirdFormation* Formation)
{
	TArray<ABlackbirdEnemyShip*> Enemies;
	Formation->CreateEnemies(Enemies);
	TArray<FVector> SpawnPoints = GetPositionsInACircle(Formation->GetActorLocation(), ForwardVector, Radius, Enemies.Num());
	for (int32 EnemyIdx = 0; EnemyIdx < Enemies.Num(); EnemyIdx++)
	{
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SpawnPoints[EnemyIdx]);
		SpawnTransform.SetRotation(ForwardVector.ToOrientationQuat());
		Enemies[EnemyIdx]->SetActorRelativeTransform(SpawnTransform);
		Enemies[EnemyIdx]->FinishSpawning(SpawnTransform);
	}
}

TArray<FVector> FFormationCircleProps::GetPositionsInACircle(const FVector& Center, const FVector& ForwardVector, const float Radius, const int32 NumPoints)
{
	TArray<FVector> Positions;

	// Ensure the forward vector is normalized
	const FVector& NormalizedForward = ForwardVector.GetSafeNormal();

	// Generate a perpendicular vector to the forward vector
	const FVector& RightVector = FVector::CrossProduct(NormalizedForward, FVector::UpVector).GetSafeNormal();
	const FVector& UpVector = FVector::CrossProduct(RightVector, NormalizedForward).GetSafeNormal();

	// Calculate positions around the circle
	for (int32 i = 0; i < NumPoints; ++i)
	{
		const float Angle = (2.0f * PI / NumPoints) * i; // Angle in radians
		FVector Offset = (FMath::Cos(Angle) * RightVector + FMath::Sin(Angle) * UpVector) * Radius;
		Positions.Add(Center + Offset);
	}

	return Positions;
}
