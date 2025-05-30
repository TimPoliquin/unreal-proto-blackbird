// Copyright Alien Shores 2025


#include "Ship/Formation/BlackbirdFormationComponent.h"

#include "Kismet/KismetMathLibrary.h"
#include "Ship/BlackbirdEnemyShip.h"
#include "Utils/ArrayUtils.h"


UBlackbirdFormationComponent::UBlackbirdFormationComponent()
{
}

void UBlackbirdFormationComponent::BeginPlay()
{
	Super::BeginPlay();
	SpawnEnemies();
}

void UBlackbirdFormationComponent::SpawnEnemies()
{
	TArray<ABlackbirdEnemyShip*> Enemies;
	TArray<FTransform> SpawnTransforms;
	CreateEnemies(Enemies);
	GetSpawnTransforms(SpawnTransforms);
	for (int32 EnemyIdx = 0; EnemyIdx < Enemies.Num(); EnemyIdx++)
	{
		Enemies[EnemyIdx]->AttachToActor(GetOwner(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		Enemies[EnemyIdx]->FinishSpawning(SpawnTransforms[EnemyIdx]);
	}
}

void UBlackbirdFormationComponent::CreateEnemies(TArray<ABlackbirdEnemyShip*>& Enemies) const
{
	for (int32 EnemyIdx = 0; EnemyIdx < EnemySpawnCount; EnemyIdx++)
	{
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(GetOwner()->GetActorLocation());
		SpawnTransform.SetRotation(GetOwner()->GetActorRotation().Quaternion());
		Enemies.Add(
			GetWorld()->SpawnActorDeferred<ABlackbirdEnemyShip>(
				UArrayUtils::GetRandomElement(EnemyClasses),
				SpawnTransform,
				GetOwner(),
				nullptr,
				ESpawnActorCollisionHandlingMethod::AlwaysSpawn
			)
		);
	}
}

void UBlackbirdFormationComponent::GetSpawnTransforms(TArray<FTransform>& OutSpawnTransforms) const
{
	switch (Shape)
	{
	case EFormationShape::Circle:
		CircleProps.GetSpawnTransforms(EnemySpawnCount, OutSpawnTransforms);
		break;
	default:
		UE_LOG(LogTemp, Warning, TEXT("[%s] Unknown formation shape: %hhd"), *GetName(), Shape);
		break;
	}
	const FVector& RootLocation = GetOwner()->GetActorLocation();
	for (FTransform& SpawnTransform : OutSpawnTransforms)
	{
		FRotator DeltaRotation = UKismetMathLibrary::MakeRotFromX(GetOwner()->GetActorForwardVector()) - UKismetMathLibrary::MakeRotFromX(
			SpawnTransform.GetRotation().GetForwardVector()
		);
		// Apply the rotation to the original forward vector
		FVector RotatedForwardVector = DeltaRotation.RotateVector(SpawnTransform.GetRotation().GetForwardVector());
		SpawnTransform.SetLocation(RootLocation + SpawnTransform.GetLocation());
		SpawnTransform.SetRotation(RotatedForwardVector.ToOrientationQuat());
	}
}
