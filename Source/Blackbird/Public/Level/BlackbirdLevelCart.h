// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlackbirdLevelCart.generated.h"

class USpringArmComponent;
class UBlackbirdTrackFollowingComponent;
class ABlackbirdLevelTrack;

UCLASS()
class BLACKBIRD_API ABlackbirdLevelCart : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABlackbirdLevelCart();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	ABlackbirdLevelTrack* GetTrack() const;
	UFUNCTION(BlueprintCallable)
	void SetTrack(ABlackbirdLevelTrack* LevelTrack);
	UFUNCTION(BlueprintCallable)
	void StartCart();
	UFUNCTION(BlueprintCallable)
	void StopCart();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Track")
	TObjectPtr<UBlackbirdTrackFollowingComponent> TrackComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Track")
	bool bAutoStart = true;

public:
	bool IsAutoStart() const;
	void SetAutoStart(const bool InAutoStart);
};
