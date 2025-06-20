// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "BlackbirdCharacter.h"
#include "BlackbirdEnemy.generated.h"

class ABlackbirdPickup;
class UBlackbirdDropPickupComponent;

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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UBlackbirdDropPickupComponent> DropComponent;
	virtual void OnReceivedDamage(const FOnReceivedDamagePayload& Payload) override;
	UFUNCTION(BlueprintImplementableEvent)
	void OnDrop(ABlackbirdPickup* Pickup);
};
