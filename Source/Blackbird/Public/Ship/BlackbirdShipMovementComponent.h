// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "BlackbirdShipMovementComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BLACKBIRD_API UBlackbirdShipMovementComponent : public UFloatingPawnMovement
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBlackbirdShipMovementComponent();

	virtual void TickComponent(
		float DeltaTime,
		ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction
	) override;

	void SetRollAmount(const float InRollDirection);
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="Movement")
	float RollTime = .5f;
	UPROPERTY(EditAnywhere, Category="Movement")
	float RollAmount = 25.f;

private:
	float InitialRollAmount = 0.f;
	float IntendedRollAmount = 0.f;
	float CurrentRollTime = 0.f;
	FVector FacingDirection = FVector::ZeroVector;
};
