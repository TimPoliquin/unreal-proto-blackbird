// Copyright Alien Shores 2025


#include "Track/Event/BlackbirdTrackEventKeyFrame.h"

#include "Blackbird/Blackbird.h"
#include "Components/BoxComponent.h"


// Sets default values
ABlackbirdTrackEventKeyFrame::ABlackbirdTrackEventKeyFrame()
{
	PrimaryActorTick.bCanEverTick = false;
	EventCollision = CreateDefaultSubobject<UBoxComponent>("EventCollision");
	EventCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	EventCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	EventCollision->SetGenerateOverlapEvents(true);
	EventCollision->SetBoxExtent(FVector(2.f, 100.f, 100.f));
}

float ABlackbirdTrackEventKeyFrame::GetKeyFrameIndex() const
{
	return KeyFrameConfig.Index;
}

void ABlackbirdTrackEventKeyFrame::SetKeyFrameConfig(const FBlackbirdTrackEventKeyFrameConfig& InConfig)
{
	KeyFrameConfig = InConfig;
}

void ABlackbirdTrackEventKeyFrame::BeginPlay()
{
	Super::BeginPlay();
	EventCollision->OnComponentBeginOverlap.AddDynamic(this, &ABlackbirdTrackEventKeyFrame::OnBeginOverlap);
}

void ABlackbirdTrackEventKeyFrame::OnBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool BFromSweep,
	const FHitResult& SweepResult
)
{
	if (KeyFrameConfig.bOneTimeTrigger && TriggerCount > 0)
	{
		return;
	}
	if (OtherActor->ActorHasTag(TAG_PLAYER))
	{
		TriggerCount++;
		OnTrackEventKeyFrameTriggeredDelegate.Broadcast(KeyFrameConfig, OtherActor, TriggerCount);
		if (KeyFrameConfig.bOneTimeTrigger)
		{
			Destroy();
		}
	}
}
