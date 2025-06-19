// Copyright Alien Shores 2025


#include "Pickup/BlackbirdPickup.h"

#include "Blackbird/Blackbird.h"
#include "Components/CapsuleComponent.h"


// Sets default values
ABlackbirdPickup::ABlackbirdPickup()
{
	PrimaryActorTick.bCanEverTick = true;
	Collision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision"));
	Collision->SetupAttachment(GetRootComponent());
	Collision->SetGenerateOverlapEvents(true);
	Collision->SetCollisionResponseToAllChannels(ECR_Ignore);
	Collision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
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
		PlayPickupEffect();
		Destroy();
	}
}

// Called every frame
void ABlackbirdPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
