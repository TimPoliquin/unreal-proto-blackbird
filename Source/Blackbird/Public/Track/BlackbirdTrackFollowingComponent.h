// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BlackbirdTrackFollowingComponent.generated.h"


class USplineComponent;
class UTimelineComponent;
class ABlackbirdTrack;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BLACKBIRD_API UBlackbirdTrackFollowingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBlackbirdTrackFollowingComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable, BlueprintPure)
	USplineComponent* GetTrack() const;
	UFUNCTION(BlueprintCallable)
	void SetTrack(USplineComponent* InTrack);
	virtual void Activate(bool bReset = false) override;
	virtual void Deactivate() override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Track", meta=(ExposeOnSpawn))
	TObjectPtr<USplineComponent> Track;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Track", meta=(ExposeOnSpawn))
	float Speed = 1000.f;

private:
	bool bActive = false;
	float Time = 0.f;
	void MoveAlongTrack() const;
};
