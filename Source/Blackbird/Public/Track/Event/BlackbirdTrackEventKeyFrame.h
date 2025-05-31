// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "BlackbirdTrackEventConfig.h"
#include "GameFramework/Actor.h"
#include "BlackbirdTrackEventKeyFrame.generated.h"

class UBoxComponent;

UCLASS()
class BLACKBIRD_API ABlackbirdTrackEventKeyFrame : public AActor
{
	GENERATED_BODY()

public:
	ABlackbirdTrackEventKeyFrame();
	float GetKeyFrameIndex() const;
	void SetKeyFrameConfig(const FBlackbirdTrackEventKeyFrameConfig& InConfig);

	FOnTrackEventKeyFrameTriggeredSignature OnTrackEventKeyFrameTriggeredDelegate;

protected:
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UBoxComponent> EventCollision;

private:
	UFUNCTION()
	void OnBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool BFromSweep,
		const FHitResult& SweepResult
	);

	UPROPERTY(VisibleInstanceOnly, Category="Track|Event|Config")
	FBlackbirdTrackEventKeyFrameConfig KeyFrameConfig;
	UPROPERTY(VisibleInstanceOnly, Category="Track|Event")
	int32 TriggerCount = 0;
};
