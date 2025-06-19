// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlackbirdPickup.generated.h"

class UCapsuleComponent;

UCLASS()
class BLACKBIRD_API ABlackbirdPickup : public AActor
{
	GENERATED_BODY()

public:
	ABlackbirdPickup();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Pickup")
	TObjectPtr<UCapsuleComponent> Collision;
	UFUNCTION(BlueprintImplementableEvent)
	void Pickup(AActor* OtherActor);
	UFUNCTION(BlueprintImplementableEvent)
	void PlayPickupEffect();

private:
	UFUNCTION()
	void OnCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                             UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                             const FHitResult& SweepResult);
};
