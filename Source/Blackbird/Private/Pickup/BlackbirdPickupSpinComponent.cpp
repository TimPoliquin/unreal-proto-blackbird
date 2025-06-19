// Copyright Alien Shores 2025


#include "Pickup/BlackbirdPickupSpinComponent.h"


UBlackbirdPickupSpinComponent::UBlackbirdPickupSpinComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UBlackbirdPickupSpinComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UBlackbirdPickupSpinComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                  FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	const float DeltaRotation = Speed * DeltaTime;
	// Apply the rotation
	const FQuat QuatRotation = FQuat(SpinAxis, FMath::DegreesToRadians(DeltaRotation));
	GetOwner()->AddActorLocalRotation(QuatRotation, false);
}
