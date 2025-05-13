// Copyright Alien Shores 2025


#include "Ship/BlackbirdShipMovementComponent.h"


UBlackbirdShipMovementComponent::UBlackbirdShipMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UBlackbirdShipMovementComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UBlackbirdShipMovementComponent::TickComponent(
	float DeltaTime,
	ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction
)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	const FRotator Rotation = UpdatedComponent->GetComponentRotation();
	if (!FMath::IsNearlyEqual(Rotation.Roll, IntendedRollAmount, 0.01f))
	{
		CurrentRollTime += DeltaTime;
		UpdatedComponent->SetWorldRotation(FRotator(Rotation.Pitch, Rotation.Yaw, FMath::Lerp(InitialRollAmount, IntendedRollAmount, CurrentRollTime / RollTime)));
	}
}

void UBlackbirdShipMovementComponent::SetRollAmount(const float InRollDirection)
{
	if (!FMath::IsNearlyEqual(InRollDirection * RollAmount, IntendedRollAmount, 0.01f))
	{
		InitialRollAmount = UpdatedComponent->GetComponentRotation().Roll;
		IntendedRollAmount = InRollDirection * RollAmount;
		CurrentRollTime = 0.f;
	}
}

