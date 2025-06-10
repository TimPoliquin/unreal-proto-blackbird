// Copyright Alien Shores 2025


#include "Track/BlackbirdTrackFollowingComponent.h"

#include "Components/SplineComponent.h"
#include "Track/BlackbirdTrackFunctionLibrary.h"


// Sets default values for this component's properties
UBlackbirdTrackFollowingComponent::UBlackbirdTrackFollowingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UBlackbirdTrackFollowingComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerPawn = Cast<APawn>(GetOwner());
	MoveAlongTrack(0);
}

void UBlackbirdTrackFollowingComponent::MoveAlongTrack(const float DeltaTime) const
{
	if (!Track)
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s] No track set on track component!"), *GetOwner()->GetName())
		return;
	}
	if (!OwnerPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s] No OwnerPawn set on track component!"), *GetOwner()->GetName())
		return;
	}
	const float Progress = Track->GetDistanceAlongSplineAtLocation(GetOwner()->GetActorLocation(), ESplineCoordinateSpace::World);
	if (!UBlackbirdTrackFunctionLibrary::HasMoreTrack(Track, Progress))
	{
		OnTrackCompleted.Broadcast(GetOwner(), Track, Track->GetSplineLength() - Progress);
		return;
	}
	const FVector ForwardVector = UBlackbirdTrackFunctionLibrary::GetRotationOnTrack(Track, Progress).Vector().GetSafeNormal();
	const FVector SplineLocation = Track->GetLocationAtDistanceAlongSpline(Progress, ESplineCoordinateSpace::World);
	const float DistanceToSpline = FVector::Dist(SplineLocation, GetOwner()->GetActorLocation());
	// slow down if you're approaching the allowed distance from the track
	if (DistanceToSpline > MaxDistanceFromSpline * .75f)
	{
		const FVector TowardSpline = (SplineLocation - GetOwner()->GetActorLocation()).GetSafeNormal();
		const FVector NewForwardVector = (ForwardVector * FMath::Max(0.f, 1.f - DistanceToSpline / MaxDistanceFromSpline) + TowardSpline * (DistanceToSpline /
			MaxDistanceFromSpline)).GetSafeNormal();
		if (bDebug)
		{
			DrawDebugDirectionalArrow(
				GetWorld(),
				GetOwner()->GetActorLocation(),
				GetOwner()->GetActorLocation() + ForwardVector * 10.f,
				1,
				FColor::Blue,
				false,
				5,
				0,
				1
			);
			DrawDebugDirectionalArrow(
				GetWorld(),
				GetOwner()->GetActorLocation(),
				GetOwner()->GetActorLocation() + TowardSpline * 10.f,
				1,
				FColor::Red,
				false,
				5,
				0,
				1
			);
			DrawDebugDirectionalArrow(
				GetWorld(),
				GetOwner()->GetActorLocation(),
				GetOwner()->GetActorLocation() + NewForwardVector * 10.f,
				1,
				FColor::Purple,
				false,
				5,
				0,
				1
			);
		}
		OwnerPawn->AddMovementInput(NewForwardVector, DeltaTime * Speed, false);
	}
	else
	{
		OwnerPawn->AddMovementInput(ForwardVector, DeltaTime * Speed, false);
	}
}


// Called every frame
void UBlackbirdTrackFollowingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (bActive)
	{
		MoveAlongTrack(DeltaTime);
	}
}

USplineComponent* UBlackbirdTrackFollowingComponent::GetTrack() const
{
	return Track;
}

void UBlackbirdTrackFollowingComponent::SetTrack(USplineComponent* InTrack)
{
	Track = InTrack;
}

void UBlackbirdTrackFollowingComponent::Activate(const bool bReset)
{
	Super::Activate(bReset);
	bActive = true;
}

void UBlackbirdTrackFollowingComponent::Deactivate()
{
	Super::Deactivate();
	bActive = false;
}

void UBlackbirdTrackFollowingComponent::SwitchToTrack(USplineComponent* NewTrack)
{
	SetTrack(NewTrack);
	MoveAlongTrack(0);
}

void UBlackbirdTrackFollowingComponent::ChangeSpeed(const float NewSpeed)
{
	Speed = NewSpeed;
}
