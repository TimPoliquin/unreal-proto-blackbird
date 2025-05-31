// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "FormationCircleProps.h"
#include "FormationShapeProps.h"
#include "GameFramework/Actor.h"
#include "BlackbirdFormationComponent.generated.h"

class ABlackbirdEnemyShip;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BLACKBIRD_API UBlackbirdFormationComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBlackbirdFormationComponent();
	void CreateEnemies(TArray<ABlackbirdEnemyShip*>& OutEnemies) const;
	void GetSpawnTransforms(TArray<FTransform>& OutSpawnTransforms) const;
	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<ABlackbirdEnemyShip*> GetEnemies() const;

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
	UPROPERTY()
	TArray<ABlackbirdEnemyShip*> Enemies;
};
