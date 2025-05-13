// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "BlackbirdShip.h"
#include "BlackbirdEnemyShip.generated.h"

UCLASS()
class BLACKBIRD_API ABlackbirdEnemyShip : public ABlackbirdShip
{
	GENERATED_BODY()

public:
	ABlackbirdEnemyShip();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

};
