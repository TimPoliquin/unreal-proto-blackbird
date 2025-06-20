// Copyright Alien Shores 2025


#include "Pickup/BlackbirdPickup.h"

#include "Blackbird/Blackbird.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
ABlackbirdPickup::ABlackbirdPickup()
{
	PrimaryActorTick.bCanEverTick = true;
	Collision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision"));
	SetRootComponent(Collision);
	Collision->SetGenerateOverlapEvents(true);
	Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Collision->SetCollisionResponseToAllChannels(ECR_Ignore);
	Collision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());
	Mesh->SetCollisionObjectType(ECC_WorldDynamic);
	Mesh->SetCollisionResponseToAllChannels(ECR_Ignore);
}

void ABlackbirdPickup::BeginPlay()
{
	Super::BeginPlay();
	Collision->OnComponentBeginOverlap.AddDynamic(this, &ABlackbirdPickup::OnCollisionBeginOverlap);
}

void ABlackbirdPickup::OnCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                               UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                               const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag(TAG_PLAYER))
	{
		Pickup(OtherActor);
		PlayPickupEffect(OtherActor);
		Destroy();
	}
}

// Called every frame
void ABlackbirdPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABlackbirdPickup::SetHomingActor(AActor* Actor, const float Delay)
{
	HomingActor = Actor;
	if (Delay > 0)
	{
		GetWorld()->GetTimerManager().SetTimer(HomingDelayTimerHandle, [this]()
		{
			if (IsValid(this))
			{
				StartHoming();
			}
		}, Delay, false);
	}
	else
	{
		StartHoming();
	}
}
