// Copyright Alien Shores 2025


#include "Targeting/TargetingUtils.h"

#include "Camera/CameraComponent.h"
#include "Kismet/KismetSystemLibrary.h"

class UCameraComponent;

void UTargetingUtils::FindActorTarget(AActor* Actor, FHitResult& OutHitResult, float TargetingDistance, bool bDebug)
{
	FVector StartingLocation;
	FVector EndingLocation;
	if (const UCameraComponent* Camera = Actor->FindComponentByClass<UCameraComponent>())
	{
		if (bDebug)
		{
			UE_LOG(LogTemp, Warning, TEXT("[UTargetingUtils] Using Camera component of [%s]"), *Actor->GetName());
		}
		StartingLocation = Camera->GetComponentLocation();
		EndingLocation = StartingLocation + FVector::UpVector * 675.f + Camera->GetForwardVector() * TargetingDistance;
	}
	else
	{
		if (bDebug)
		{
			UE_LOG(LogTemp, Warning, TEXT("[UTargetingUtils] Using actor location of [%s]"), *Actor->GetName());
		}
		StartingLocation = Actor->GetActorLocation();
		EndingLocation = StartingLocation + Actor->GetActorForwardVector() * TargetingDistance;
	}
	if (bDebug)
	{
		DrawDebugSphere(Actor->GetWorld(), StartingLocation, 10.f, 20, FColor::Green, false, 10);
		DrawDebugSphere(Actor->GetWorld(), EndingLocation, 10.f, 20, FColor::Red, false, 10);
		UE_LOG(
			LogTemp,
			Warning,
			TEXT("[UTargetingUtils] performing line trace from [%s] -> [%s]"),
			*StartingLocation.ToString(),
			*EndingLocation.ToString()
		);
	}
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(Actor);
	UKismetSystemLibrary::LineTraceSingle(
		Actor,
		StartingLocation,
		EndingLocation,
		TraceTypeQuery1,
		false,
		ActorsToIgnore,
		bDebug
			? EDrawDebugTrace::ForDuration
			: EDrawDebugTrace::None,
		OutHitResult,
		true
	);
	if (!OutHitResult.bBlockingHit)
	{
		if (bDebug)
		{
			UE_LOG(
				LogTemp,
				Warning,
				TEXT("[UTargetingUtils] No actors found on line trace for %s. Setting impact point to line trace end location."),
				*Actor->GetName()
			)
		}
		OutHitResult.ImpactPoint = EndingLocation;
	}
}

FVector UTargetingUtils::CalculateInterceptVector(const AActor* Instigator, const AActor* Target, const float TimeToIntercept)
{
	// Calculate the future position of the target
	const FVector FutureTargetPosition = Target->GetActorLocation() + (Target->GetVelocity() * TimeToIntercept);

	// Calculate the required velocity to reach the future position in the given time
	const FVector RequiredVelocity = (FutureTargetPosition - Instigator->GetActorLocation()) / TimeToIntercept;

	// Return the direction vector (normalized)
	return RequiredVelocity;
}

float UTargetingUtils::CalculateAngleBetweenVectors(const FVector& VectorA, const FVector& VectorB)
{
	const FVector NormalizedA = VectorA.GetSafeNormal();
	const FVector NormalizedB = VectorB.GetSafeNormal();
	const float DotProduct = FMath::Clamp(FVector::DotProduct(NormalizedA, NormalizedB), -1.f, 1.f);
	const float AngleRadians = FMath::Acos(DotProduct);
	const float AngleDegrees = FMath::RadiansToDegrees(AngleRadians);
	return AngleDegrees;
}
