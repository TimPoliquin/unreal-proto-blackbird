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

FVector UTargetingUtils::CalculateInterceptVector(const AActor* Instigator, const AActor* Target, const float Speed)
{
	const FVector ShooterLocation = Instigator->GetActorLocation();
	const FVector TargetLocation = Target->GetActorLocation();
	const FVector TargetVelocity = Target->GetVelocity();
	const FVector ToTarget = TargetLocation - ShooterLocation;

	// Calculate the relative velocity
	const FVector RelativeVelocity = TargetVelocity;

	// Quadratic equation coefficients
	const float A = RelativeVelocity.SizeSquared() - FMath::Square(Speed);
	const float B = 2.0f * FVector::DotProduct(RelativeVelocity, ToTarget);
	const float C = ToTarget.SizeSquared();

	// Solve the quadratic equation
	const float Discriminant = FMath::Square(B) - 4.0f * A * C;

	if (Discriminant < 0.0f)
	{
		// No solution, target cannot be hit
		return FVector::ZeroVector;
	}

	// Calculate the time to impact
	const float TimeToImpact = (-B - FMath::Sqrt(Discriminant)) / (2.0f * A);

	if (TimeToImpact < 0.0f)
	{
		// Negative time, target cannot be hit
		return FVector::ZeroVector;
	}

	// Calculate the intercept point
	const FVector InterceptPoint = TargetLocation + TargetVelocity * TimeToImpact;

	// Calculate the required velocity to hit the intercept point
	const FVector RequiredVelocity = (InterceptPoint - ShooterLocation).GetSafeNormal() * Speed;

	return RequiredVelocity;
}
