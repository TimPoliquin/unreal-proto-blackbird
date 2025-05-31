// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "BlackbirdShip.h"
#include "Targeting/TargetableInterface.h"
#include "BlackbirdEnemyShip.generated.h"

UCLASS()
class BLACKBIRD_API ABlackbirdEnemyShip : public ABlackbirdShip, public ITargetableInterface
{
	GENERATED_BODY()

public:
	ABlackbirdEnemyShip();
	virtual void Tick(float DeltaTime) override;
	virtual void Mark_Implementation() override;
	virtual void Unmark_Implementation() override;
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void Attack();

protected:
	virtual void BeginPlay() override;
};
