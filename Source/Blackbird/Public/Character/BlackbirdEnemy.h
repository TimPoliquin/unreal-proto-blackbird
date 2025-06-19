// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "BlackbirdCharacter.h"
#include "BlackbirdEnemy.generated.h"

UCLASS()
class BLACKBIRD_API ABlackbirdEnemy : public ABlackbirdCharacter
{
	GENERATED_BODY()

public:
	ABlackbirdEnemy();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void Attack();

protected:
	virtual void BeginPlay() override;
};
