// Copyright Alien Shores 2025


#include "Track/Event/BlackbirdTrackEvent.h"

#include "Track/BlackbirdTrackTags.h"
#include "Track/Event/BlackbirdTrackEventKeyFrame.h"


// Sets default values
ABlackbirdTrackEvent::ABlackbirdTrackEvent()
{
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ABlackbirdTrackEvent::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(StartKeyFrame))
	{
		StartKeyFrame->OnTrackEventKeyFrameTriggeredDelegate.AddDynamic(this, &ABlackbirdTrackEvent::OnTrackEventTriggered);
	}
	if (IsValid(EndKeyFrame))
	{
		EndKeyFrame->OnTrackEventKeyFrameTriggeredDelegate.AddDynamic(this, &ABlackbirdTrackEvent::OnTrackEventTriggered);
	}
	for (ABlackbirdTrackEventKeyFrame* KeyFrame : KeyFrames)
	{
		KeyFrame->OnTrackEventKeyFrameTriggeredDelegate.AddDynamic(this, &ABlackbirdTrackEvent::OnTrackEventTriggered);
	}
}

void ABlackbirdTrackEvent::GenerateEventKeyFrames(const FBlackbirdTrackEventContext& Context)
{
	// cleanup removed keyframes
	TrackEventConfig = Context.TrackEventConfig;
	for (int32 EventIdx = TrackEventConfig.Keys.Num(); EventIdx < KeyFrames.Num(); EventIdx++)
	{
		GetWorld()->DestroyActor(KeyFrames[EventIdx]);
	}
	KeyFrames.SetNum(TrackEventConfig.Keys.Num());
	// create start key frame
	GenerateStartKeyFrameInstance(Context);
	// create the in-between key frames
	for (int32 KeyFrameIdx = 0; KeyFrameIdx < TrackEventConfig.Keys.Num(); KeyFrameIdx++)
	{
		FBlackbirdTrackEventKeyFrameConfig& KeyFrame = TrackEventConfig.Keys[KeyFrameIdx];
		if (ABlackbirdTrackEventKeyFrame* KeyFrameInstance = KeyFrames[KeyFrameIdx]; IsValid(KeyFrameInstance))
		{
			UpdateKeyFrameInstance(KeyFrameInstance, KeyFrame, Context);
		}
		else
		{
			KeyFrames.Add(GenerateKeyFrameInstance(KeyFrame, Context));
		}
	}
	// create end key frame if the length is greater than 0
	if (TrackEventConfig.Length > 0)
	{
		GenerateEndKeyFrameInstance(Context);
	}
}

void ABlackbirdTrackEvent::GenerateStartKeyFrameInstance(const FBlackbirdTrackEventContext& Context)
{
	FBlackbirdTrackEventKeyFrameConfig StartConfig;
	StartConfig.Index = 0;
	StartConfig.Name = FName("Start");
	StartConfig.KeyFrameTag = FBlackbirdTrackTags::Get().Track_Event_Start;
	StartConfig.bOneTimeTrigger = TrackEventConfig.bOneTimeTrigger;
	if (IsValid(StartKeyFrame))
	{
		UpdateKeyFrameInstance(StartKeyFrame, StartConfig, Context);
	}
	else
	{
		StartKeyFrame = GenerateKeyFrameInstance(StartConfig, Context);
	}
}

void ABlackbirdTrackEvent::GenerateEndKeyFrameInstance(const FBlackbirdTrackEventContext& Context)
{
	FBlackbirdTrackEventKeyFrameConfig EndConfig;
	EndConfig.Index = TrackEventConfig.Length;
	EndConfig.Name = FName("End");
	EndConfig.KeyFrameTag = FBlackbirdTrackTags::Get().Track_Event_End;
	EndConfig.bOneTimeTrigger = TrackEventConfig.bOneTimeTrigger;
	if (IsValid(EndKeyFrame))
	{
		UpdateKeyFrameInstance(EndKeyFrame, EndConfig, Context);
	}
	else
	{
		EndKeyFrame = GenerateKeyFrameInstance(EndConfig, Context);
	}
}

ABlackbirdTrackEventKeyFrame* ABlackbirdTrackEvent::GenerateKeyFrameInstance(
	const FBlackbirdTrackEventKeyFrameConfig& KeyFrame,
	const FBlackbirdTrackEventContext& Context
)
{
	FTransform Transform;
	Transform.SetLocation(Context.GetEventKeyFrameLocation(KeyFrame.Index));
	Transform.SetRotation(Context.GetEventKeyFrameRotation(KeyFrame.Index).Quaternion());
	ABlackbirdTrackEventKeyFrame* KeyFrameInstance = GetWorld()->SpawnActorDeferred<ABlackbirdTrackEventKeyFrame>(
		ABlackbirdTrackEventKeyFrame::StaticClass(),
		Transform
	);
	UpdateKeyFrameInstance(KeyFrameInstance, KeyFrame, Context);
	KeyFrameInstance->FinishSpawning(Transform);
	return KeyFrameInstance;
}

void ABlackbirdTrackEvent::UpdateKeyFrameInstance(
	ABlackbirdTrackEventKeyFrame* KeyFrameInstance,
	const FBlackbirdTrackEventKeyFrameConfig& KeyFrame,
	const FBlackbirdTrackEventContext& Context
)
{
	KeyFrameInstance->SetActorLocationAndRotation(Context.GetEventKeyFrameLocation(KeyFrame.Index), Context.GetEventKeyFrameRotation(KeyFrame.Index));
	KeyFrameInstance->SetKeyFrameConfig(KeyFrame);
	KeyFrameInstance->SetActorLabel(FString::Printf(TEXT("%s:%s"), *GetName(), *KeyFrame.Name.ToString()));
	KeyFrameInstance->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
}
