// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "BlackbirdTrackEventConfig.h"
#include "GameFramework/Actor.h"
#include "BlackbirdTrackEventBase.generated.h"

class UBoxComponent;

UCLASS(Abstract)
class BLACKBIRD_API ABlackbirdTrackEventBase : public AActor
{
	GENERATED_BODY()

public:
	ABlackbirdTrackEventBase();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	virtual EBlackbirdTrackEventType GetTrackEventType() const { return EBlackbirdTrackEventType::None; };

protected:
	virtual void BeginPlay() override;
	virtual void SetupTriggers();
	UFUNCTION()
	virtual void OnTrackEventTriggered(AActor* TriggeringActor, const FBlackbirdTrackEventTriggeredPayload& Data);
	UFUNCTION(BlueprintImplementableEvent)
	void HandleTrackEvent(AActor* TriggeringActor, const FBlackbirdTrackEventTriggeredPayload& Data);
	UPROPERTY(BlueprintAssignable)
	FOnTrackEventTriggeredSignature OnTrackEventTriggeredDelegate;
};
