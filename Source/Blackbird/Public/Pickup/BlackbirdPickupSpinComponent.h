// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BlackbirdPickupSpinComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BLACKBIRD_API UBlackbirdPickupSpinComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBlackbirdPickupSpinComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Spin")
	FVector SpinAxis = FVector::UpVector;
	UPROPERTY(EditANywhere, BlueprintReadOnly, Category="Spin")
	float Speed = 180.f;
};
