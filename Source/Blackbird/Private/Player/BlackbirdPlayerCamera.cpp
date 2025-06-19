// Copyright Alien Shores 2025


#include "Player/BlackbirdPlayerCamera.h"

#include "Camera/CameraComponent.h"
#include "Components/SplineComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/BlackbirdPlayerCharacter.h"
#include "Track/BlackbirdTrackFollowingComponent.h"
#include "Track/TrackFollowingActorInterface.h"


// Sets default values
ABlackbirdPlayerCamera::ABlackbirdPlayerCamera()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent")));
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	SpringArmComponent->bInheritPitch = false;
	SpringArmComponent->bInheritYaw = true;
	SpringArmComponent->bInheritRoll = false;
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->bUsePawnControlRotation = false;
}

// Called when the game starts or when spawned
void ABlackbirdPlayerCamera::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABlackbirdPlayerCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsValid(FollowActor.GetObject()))
	{
		const USplineComponent* Spline = FollowActor.GetInterface()->GetTrackFollowingComponent()->GetTrack();
		const float DistanceOnTrack = FollowActor.GetInterface()->GetTrackFollowingComponent()->GetTrackDistance();
		const FTransform SplineTransform = Spline->GetTransformAtDistanceAlongSpline(
			DistanceOnTrack, ESplineCoordinateSpace::World
		);
		SetActorLocation(SplineTransform.GetLocation());
		if (GetOwner()->GetInstigatorController())
		{
			SetActorRotation(
				GetOwner()->GetInstigatorController()->GetControlRotation().Quaternion()
			);
		}
		else
		{
			SetActorRotation(SplineTransform.GetRotation());
		}
	}
}

void ABlackbirdPlayerCamera::SetFollowActor(AActor* InFollowActor)
{
	if (IsValid(InFollowActor) && InFollowActor->Implements<UTrackFollowingActorInterface>())
	{
		SetOwner(InFollowActor);
		FollowActor.SetObject(InFollowActor);
		FollowActor.SetInterface(Cast<ITrackFollowingActorInterface>(InFollowActor));
		if (ABlackbirdPlayerCharacter* PlayerCharacter = Cast<ABlackbirdPlayerCharacter>(InFollowActor))
		{
			PlayerCharacter->SetPlayerCamera(this);
		}
	}
}

UCameraComponent* ABlackbirdPlayerCamera::GetCameraComponent() const
{
	return CameraComponent;
}
