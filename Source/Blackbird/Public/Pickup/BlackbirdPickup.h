// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Attribute/BlackbirdAttributeSetTypes.h"
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
	void SetHomingActor(AActor* Actor, const float Delay = 0.f);

protected:
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Pickup")
	TObjectPtr<UCapsuleComponent> Collision;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Pickup")
	TObjectPtr<UStaticMeshComponent> Mesh;
	UPROPERTY(BlueprintReadWrite, Category="Pickup")
	TObjectPtr<AActor> HomingActor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pickup")
	float HomingForce = 1000.f;
	UFUNCTION(BlueprintImplementableEvent)
	void Pickup(AActor* OtherActor);
	UFUNCTION(BlueprintImplementableEvent)
	void PlayPickupEffect(AActor* OtherActor);
	UFUNCTION(BlueprintImplementableEvent)
	void StartHoming();

private:
	UFUNCTION()
	void OnCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                             UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                             const FHitResult& SweepResult);

	FTimerHandle HomingDelayTimerHandle;
};
