// Copyright Alien Shores 2025


#include "Player/PlayerTargetingComponent.h"

#include "Targeting/TargetableInterface.h"


UPlayerTargetingComponent::UPlayerTargetingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UPlayerTargetingComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPlayerTargetingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UPlayerTargetingComponent::Activate(const bool bReset)
{
	Super::Activate(bReset);
	bActive = true;
}

void UPlayerTargetingComponent::Deactivate()
{
	Super::Deactivate();
	bActive = false;
}

void UPlayerTargetingComponent::CursorTrace(const APlayerController* PlayerController)
{
	PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, CursorTraceHit);
	if (CursorTraceHit.bBlockingHit)
	{
		TrackTarget(CursorTraceHit.GetActor());
	}
	else
	{
		ClearTarget();
	}
}

bool UPlayerTargetingComponent::HasTarget() const
{
	return CursorTraceHit.bBlockingHit;
}


void UPlayerTargetingComponent::TrackTarget(AActor* Actor)
{
	LastTarget = CurrentTarget;
	if (IsValid(Actor) && Actor->Implements<UTargetableInterface>())
	{
		CurrentTarget = Actor;
		TargetingStatus = ETargetingStatus::TargetingEnemy;
	}
	else
	{
		CurrentTarget = nullptr;
		TargetingStatus = ETargetingStatus::NotTargeting;
	}
	if (CurrentTarget != LastTarget)
	{
		ITargetableInterface::Unmark(LastTarget);
		ITargetableInterface::Mark(CurrentTarget);
		OnPlayerTargetingChangedDelegate.Broadcast(CurrentTarget, TargetingStatus);
	}
}

void UPlayerTargetingComponent::ClearTarget()
{
	CurrentTarget = nullptr;
	LastTarget = nullptr;
	TargetingStatus = ETargetingStatus::NotTargeting;
	OnPlayerTargetingChangedDelegate.Broadcast(CurrentTarget, TargetingStatus);
}
