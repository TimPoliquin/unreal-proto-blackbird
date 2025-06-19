// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BlackbirdTrackFollowingComponent.generated.h"


class UCharacterMovementComponent;
class USplineComponent;
class UTimelineComponent;
class ABlackbirdTrack;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnTrackCompleted, AActor*, Cart, const USplineComponent*, Track,
                                               const float, Overflow);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BLACKBIRD_API UBlackbirdTrackFollowingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBlackbirdTrackFollowingComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	UFUNCTION(BlueprintCallable, BlueprintPure)
	USplineComponent* GetTrack() const;
	UFUNCTION(BlueprintCallable)
	void SetTrack(USplineComponent* InTrack);
	virtual void Activate(bool bReset = false) override;
	virtual void Deactivate() override;
	UFUNCTION(BlueprintCallable)
	void SwitchToTrack(USplineComponent* NewTrack);
	UFUNCTION(BlueprintCallable)
	void ChangeSpeed(const float NewSpeed);
	void AddMovementInput(const FVector2D& InInputMovement);
	void ClearMovementInput();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetTrackDistance() const;

	UPROPERTY(BlueprintAssignable)
	FOnTrackCompleted OnTrackCompleted;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Track", meta=(ExposeOnSpawn))
	TObjectPtr<USplineComponent> Track;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Track", meta=(ExposeOnSpawn))
	float Speed = 1000.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Track", meta=(ExposeOnSpawn))
	float MaxDistanceFromSpline = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Debug", meta=(ExposeOnSpawn))
	bool bDebug = false;

private:
	void MoveAlongTrack(float DeltaTime);
	UPROPERTY()
	TObjectPtr<APawn> OwnerPawn;
	UPROPERTY(Replicated)
	bool bActive = false;
	UPROPERTY(Replicated)
	FVector2D MovementInput = FVector2D::ZeroVector;
	float DistanceOnTrack = 0.f;
};
