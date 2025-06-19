// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "MoveTarget.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FMoveTarget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector StartingLocation = FVector::ZeroVector;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector EndingLocation = FVector::ZeroVector;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator StartingRotation = FRotator::ZeroRotator;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator EndingRotation = FRotator::ZeroRotator;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Duration = 0.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bActive = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bDelayed = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Time = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Delay = 1.f;

	bool IsActive() const
	{
		return bActive;
	}

	void Deactivate()
	{
		bActive = false;
	}

	void IncrementTime(const float DeltaTime)
	{
		Time += DeltaTime;
		if (bDelayed)
		{
			if (Time >= Delay)
			{
				bDelayed = false;
				Time = Time - Delay;
			}
		}
		else if (Time >= Duration)
		{
			bActive = false;
		}
	}

	FVector GetLocation() const
	{
		if (bDelayed)
		{
			return StartingLocation;
		}
		if (Time < Duration)
		{
			return FMath::Lerp(StartingLocation, EndingLocation, Time / Duration);
		}
		return EndingLocation;
	}

	FRotator GetRotation() const
	{
		if (bDelayed)
		{
			return StartingRotation;
		}
		if (Time < Duration)
		{
			return FMath::Lerp(StartingRotation, EndingRotation, Time / Duration);
		}
		return EndingRotation;
	}

	static FMoveTarget GetReturnToRelativeOrigin(const AActor* Actor, const float InDuration = 2.f, const float InDelay = 0.5f)
	{
		FMoveTarget Target;
		Target.StartingLocation = Actor->GetRootComponent()->GetRelativeLocation();
		Target.EndingLocation = FVector::ZeroVector;
		Target.StartingRotation = Actor->GetRootComponent()->GetRelativeRotation();
		Target.EndingRotation = FRotator::ZeroRotator;
		Target.Delay = InDelay;
		Target.Duration = InDuration;
		Target.bActive = true;
		Target.bDelayed = InDelay > 0.f;
		return Target;
	}
};
