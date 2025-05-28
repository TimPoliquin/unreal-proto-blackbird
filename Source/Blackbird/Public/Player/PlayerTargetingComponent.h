// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerTargetingComponent.generated.h"


UENUM(BlueprintType)
enum class ETargetingStatus : uint8
{
	NotTargeting,
	TargetingEnemy,
	TargetingOther,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerTargetingChangedSignature, const AActor*, Target, const ETargetingStatus&, Status);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BLACKBIRD_API UPlayerTargetingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPlayerTargetingComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void Activate(bool bReset = false) override;
	virtual void Deactivate() override;

	void CursorTrace(const APlayerController* PlayerController);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Player Targeting")
	bool HasTarget() const;

	UPROPERTY(BlueprintAssignable, Category="Player Targeting")
	FOnPlayerTargetingChangedSignature OnPlayerTargetingChangedDelegate;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Player Targeting")
	bool bActive = true;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Player Targeting")
	ETargetingStatus TargetingStatus = ETargetingStatus::NotTargeting;

private:
	FHitResult CursorTraceHit;
	UPROPERTY()
	TObjectPtr<AActor> LastTarget;
	UPROPERTY()
	TObjectPtr<AActor> CurrentTarget;

	void TrackTarget(AActor* Actor);
	void ClearTarget();
};
