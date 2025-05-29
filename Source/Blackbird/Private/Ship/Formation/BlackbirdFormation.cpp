// Copyright Alien Shores 2025


#include "Ship/Formation/BlackbirdFormation.h"

#include "Ship/BlackbirdEnemyShip.h"
#include "Utils/ArrayUtils.h"


ABlackbirdFormation::ABlackbirdFormation()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABlackbirdFormation::BeginPlay()
{
	Super::BeginPlay();
	SpawnEnemies();
}

void ABlackbirdFormation::SpawnEnemies()
{
	switch (Shape)
	{
	case EFormationShape::Circle:
		CircleProps.SpawnEnemies(this);
		break;
	default:
		UE_LOG(LogTemp, Warning, TEXT("[%s] Unknown formation shape: %hhd"), *GetName(), Shape);
		break;
	}
}

void ABlackbirdFormation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABlackbirdFormation::CreateEnemies(TArray<ABlackbirdEnemyShip*>& Enemies)
{
	for (int32 EnemyIdx = 0; EnemyIdx < EnemySpawnCount; EnemyIdx++)
	{
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(GetActorLocation());
		SpawnTransform.SetRotation(GetActorRotation().Quaternion());
		Enemies.Add(
			GetWorld()->SpawnActorDeferred<ABlackbirdEnemyShip>(
				UArrayUtils::GetRandomElement(EnemyClasses),
				SpawnTransform,
				this,
				nullptr,
				ESpawnActorCollisionHandlingMethod::AlwaysSpawn
			)
		);
	}
}
