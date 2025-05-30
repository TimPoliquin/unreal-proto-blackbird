// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlackbirdCart.generated.h"

class USplineComponent;
class USpringArmComponent;
class UBlackbirdTrackFollowingComponent;
class ABlackbirdTrack;

UCLASS()
class BLACKBIRD_API ABlackbirdCart : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABlackbirdCart();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	USplineComponent* GetTrack() const;
	UFUNCTION(BlueprintCallable)
	void SetTrack(USplineComponent* Track);
	UFUNCTION(BlueprintCallable)
	void StartCart();
	UFUNCTION(BlueprintCallable)
	void StopCart();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Track")
	TObjectPtr<UBlackbirdTrackFollowingComponent> TrackComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Track", meta=(ExposeOnSpawn))
	bool bAutoStart = true;

public:
	bool IsAutoStart() const;
	void SetAutoStart(const bool InAutoStart);
};
