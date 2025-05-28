// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BlackbirdTrackFollowingComponent.generated.h"


class UTimelineComponent;
class ABlackbirdLevelTrack;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BLACKBIRD_API UBlackbirdTrackFollowingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBlackbirdTrackFollowingComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	ABlackbirdLevelTrack* GetTrack();
	void SetTrack(ABlackbirdLevelTrack* InTrack);
	virtual void Activate(bool bReset = false) override;
	virtual void Deactivate() override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Track")
	TObjectPtr<ABlackbirdLevelTrack> Track;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Track")
	float Speed = 120.f;

private:
	bool bActive = false;
	float Time = 0.f;
	void MoveAlongTrack();
};
