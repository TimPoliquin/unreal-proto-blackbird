// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "FormationCircleProps.h"
#include "FormationShapeProps.h"
#include "GameFramework/Actor.h"
#include "BlackbirdFormation.generated.h"

class ABlackbirdEnemyShip;

UCLASS()
class BLACKBIRD_API ABlackbirdFormation : public AActor
{
	GENERATED_BODY()

public:
	ABlackbirdFormation();
	virtual void Tick(float DeltaTime) override;
	void CreateEnemies(TArray<ABlackbirdEnemyShip*>& Enemies);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Formation")
	TArray<TSubclassOf<ABlackbirdEnemyShip>> EnemyClasses;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Formation")
	int32 EnemySpawnCount = 1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Formation")
	EFormationShape Shape = EFormationShape::Circle;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Formation", meta=(EditCondition="Shape == EFormationShape::Circle", EditConditionHides))
	FFormationCircleProps CircleProps;

private:
	void SpawnEnemies();
};
