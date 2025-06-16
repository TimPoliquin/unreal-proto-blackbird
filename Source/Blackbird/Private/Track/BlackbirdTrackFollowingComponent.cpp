// Copyright Alien Shores 2025


#include "Track/BlackbirdTrackFollowingComponent.h"

#include "Components/SplineComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"
#include "Track/BlackbirdTrackFunctionLibrary.h"


// Sets default values for this component's properties
UBlackbirdTrackFollowingComponent::UBlackbirdTrackFollowingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);
}


// Called when the game starts
void UBlackbirdTrackFollowingComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerPawn = Cast<APawn>(GetOwner());
	MoveAlongTrack(0);
}

void UBlackbirdTrackFollowingComponent::MoveAlongTrack(const float DeltaTime)
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
	const FTransform SplineTransform = Track->GetTransformAtDistanceAlongSpline(Progress, ESplineCoordinateSpace::World);
	const FVector SplineForwardVector = SplineTransform.Rotator().Vector().GetSafeNormal();
	const FVector InputMovementVector = UKismetMathLibrary::InverseTransformDirection(
		SplineTransform,
		FVector::UpVector * MovementInput.Y + FVector::RightVector * MovementInput.X
	);
	const FVector SplineLocation = SplineTransform.GetLocation();
	const float DistanceToSpline = FVector::Dist(SplineLocation, GetOwner()->GetActorLocation());
	// slow down if you're approaching the allowed distance from the track
	if (DistanceToSpline > MaxDistanceFromSpline * .75f)
	{
		const FVector TowardSpline = (SplineLocation - GetOwner()->GetActorLocation()).GetSafeNormal();
		const FVector NewForwardVector = (SplineForwardVector * FMath::Max(0.f, 1.f - DistanceToSpline / MaxDistanceFromSpline) + TowardSpline * (
			DistanceToSpline /
			MaxDistanceFromSpline)).GetSafeNormal();
		if (bDebug)
		{
			DrawDebugSphere(GetWorld(), SplineLocation, MaxDistanceFromSpline, 12, FColor(255, 0, 0, 100), false, 0, 0, 1.f);
			DrawDebugDirectionalArrow(
				GetWorld(),
				GetOwner()->GetActorLocation(),
				GetOwner()->GetActorLocation() + SplineForwardVector * 10.f,
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
				GetOwner()->GetActorLocation() + InputMovementVector * 10.f,
				1,
				FColor::Green,
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
	else if (DistanceToSpline < MaxDistanceFromSpline)
	{
		const FVector ForwardVector = (SplineForwardVector + InputMovementVector).GetSafeNormal();
		OwnerPawn->AddMovementInput(ForwardVector, DeltaTime * Speed, false);
	}
	MovementInput = FVector2D::ZeroVector;
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

void UBlackbirdTrackFollowingComponent::GetLifetimeReplicatedProps(
	TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UBlackbirdTrackFollowingComponent, bActive)
	DOREPLIFETIME(UBlackbirdTrackFollowingComponent, MovementInput)
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

void UBlackbirdTrackFollowingComponent::AddMovementInput(const FVector2D& InInputMovement)
{
	MovementInput += InInputMovement;
}

void UBlackbirdTrackFollowingComponent::ClearMovementInput()
{
	MovementInput = FVector2D::ZeroVector;
}