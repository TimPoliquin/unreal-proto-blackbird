// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "BlackbirdTrackEventTriggerComponent.h"
#include "BlackbirdTrackEventTimedTriggerComponent.generated.h"

USTRUCT()
struct FActiveEvent
{
	GENERATED_BODY()

	UPROPERTY()
	TObjectPtr<AActor> Actor = nullptr;
	float CurrentDuration = 0.f;
	int32 TriggerCount = 0;
};

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BLACKBIRD_API UBlackbirdTrackEventTimedTriggerComponent : public UBlackbirdTrackEventTriggerComponent
{
	GENERATED_BODY()

public:
	UBlackbirdTrackEventTimedTriggerComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;
	virtual void FireTrigger(AActor* Actor, int32 InTriggerCount) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Trigger Component|Duration")
	FName EndEventName = FName("");
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Trigger Component|Duration")
	FGameplayTag EndEventTag = FGameplayTag::EmptyTag;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Trigger Component")
	float Duration = 0.f;

private:
	bool bActive = true;
	TArray<FActiveEvent> ActiveEvents;

	void ProcessActiveEvents(float DeltaTime);
	virtual void Activate(bool bReset) override;
	virtual void Deactivate() override;
};
