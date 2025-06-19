// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "FormationCircleProps.h"
#include "FormationShapeProps.h"
#include "GameFramework/Actor.h"
#include "BlackbirdFormationComponent.generated.h"

class ABlackbirdEnemy;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BLACKBIRD_API UBlackbirdFormationComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBlackbirdFormationComponent();
	void CreateEnemies(TArray<ABlackbirdEnemy*>& OutEnemies) const;
	void GetSpawnTransforms(TArray<FTransform>& OutSpawnTransforms) const;
	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<ABlackbirdEnemy*> GetEnemies() const;
	UFUNCTION(BlueprintCallable)
	void SpawnEnemies();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Formation")
	TArray<TSubclassOf<ABlackbirdEnemy>> EnemyClasses;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Formation")
	int32 EnemySpawnCount = 1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Formation")
	EFormationShape Shape = EFormationShape::Circle;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Formation",
		meta=(EditCondition="Shape == EFormationShape::Circle", EditConditionHides))
	FFormationCircleProps CircleProps;

private:
	UPROPERTY()
	TArray<ABlackbirdEnemy*> Enemies;
};
