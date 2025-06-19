// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "BlackbirdPlayerStart.generated.h"

class ABlackbirdPlayerCamera;
class ABlackbirdTrackEventSpline;
class USplineComponent;
class ITrackInterface;
class ABlackbirdTrack;

UCLASS()
class BLACKBIRD_API ABlackbirdPlayerStart : public APlayerStart
{
	GENERATED_BODY()

public:
	ABlackbirdPlayerStart(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	USplineComponent* GetTrack() const;
	UFUNCTION(BlueprintCallable, BlueprintPure)
	ABlackbirdPlayerCamera* GetCameraActor() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Track")
	TObjectPtr<ABlackbirdTrackEventSpline> Track;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Track")
	TObjectPtr<ABlackbirdPlayerCamera> CameraActor;
};
