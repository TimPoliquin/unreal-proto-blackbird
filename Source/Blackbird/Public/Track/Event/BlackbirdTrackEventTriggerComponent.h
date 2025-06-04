// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Track/Event/BlackbirdTrackEventConfig.h"
#include "BlackbirdTrackEventTriggerComponent.generated.h"


class UBoxComponent;

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BLACKBIRD_API UBlackbirdTrackEventTriggerComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	UBlackbirdTrackEventTriggerComponent();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	virtual int32 GetTriggerCount() const;
	UFUNCTION(BlueprintCallable, BlueprintPure)
	virtual bool CanTrigger() const;
	int32 GetSplinePointIndex() const;
	void SetSplinePointIndex(int32 InSplinePointIndex);
	UPROPERTY(BlueprintAssignable, Category="Track|Event")
	FOnTrackEventTriggeredSignature OnTrackEventTriggeredDelegate;

protected:
	virtual void BeginPlay() override;
	virtual void FireTrigger(AActor* Actor, int32 InTriggerCount);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Trigger Component")
	TObjectPtr<UBoxComponent> TriggerBox;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Trigger Component")
	FName EventName = FName("");
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Trigger Component")
	FGameplayTag EventTag = FGameplayTag::EmptyTag;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Trigger Component")
	int32 MaxTriggerCount = -1;
	// the tags that the colliding actor must have in order to actually trigger this event
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Trigger Component")
	TArray<FName> TriggerActorTags;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Trigger Component|Spline")
	int32 SplinePointIndex = -1;

private:
	int32 TriggerCount = 0;
	bool IsTriggeringActor(const AActor* Actor) const;
	UFUNCTION()
	virtual void OnTriggerBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool BFromSweep,
		const FHitResult& SweepResult
	);
};
