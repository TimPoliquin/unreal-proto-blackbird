// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlackbirdSquadron.generated.h"

class USplineComponent;
class UBlackbirdFormationComponent;

UCLASS()
class BLACKBIRD_API ABlackbirdSquadron : public AActor
{
	GENERATED_BODY()

public:
	ABlackbirdSquadron();

	UFUNCTION(BlueprintCallable)
	void SetTrack(USplineComponent* InTrack);
	UFUNCTION(BlueprintCallable)
	void Spawn() const;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Formation")
	TObjectPtr<UBlackbirdFormationComponent> FormationComponent;
	UPROPERTY()
	USplineComponent* Track;

private:
	void SetTrackOnChildren() const;
};
