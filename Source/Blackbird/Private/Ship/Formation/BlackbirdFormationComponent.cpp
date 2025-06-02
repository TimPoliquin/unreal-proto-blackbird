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
	Enemies.Empty();
	SpawnEnemies();
}

void UBlackbirdFormationComponent::SpawnEnemies()
{
	TArray<ABlackbirdEnemyShip*> EnemySpawns;
	TArray<FTransform> SpawnTransforms;
	CreateEnemies(EnemySpawns);
	GetSpawnTransforms(SpawnTransforms);
	for (int32 EnemyIdx = 0; EnemyIdx < EnemySpawns.Num(); EnemyIdx++)
	{
		EnemySpawns[EnemyIdx]->AttachToActor(GetOwner(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		EnemySpawns[EnemyIdx]->FinishSpawning(SpawnTransforms[EnemyIdx]);
	}
	Enemies.Append(EnemySpawns);
}

void UBlackbirdFormationComponent::CreateEnemies(TArray<ABlackbirdEnemyShip*>& OutEnemies) const
{
	for (int32 EnemyIdx = 0; EnemyIdx < EnemySpawnCount; EnemyIdx++)
	{
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(GetOwner()->GetActorLocation());
		SpawnTransform.SetRotation(GetOwner()->GetActorRotation().Quaternion());
		OutEnemies.Add(
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
	const FTransform& RootTransform = GetOwner()->GetActorTransform();
	for (FTransform& SpawnTransform : OutSpawnTransforms)
	{
		SpawnTransform.SetLocation(UKismetMathLibrary::TransformLocation(RootTransform, SpawnTransform.GetLocation()));
		SpawnTransform.SetRotation(UKismetMathLibrary::TransformRotation(RootTransform, SpawnTransform.GetRotation().Rotator()).Quaternion());
	}
}

TArray<ABlackbirdEnemyShip*> UBlackbirdFormationComponent::GetEnemies() const
{
	return Enemies;
}
