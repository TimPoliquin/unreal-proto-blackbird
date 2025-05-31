// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "BlackbirdPlayerStart.generated.h"

class ABlackbirdTrack;

UCLASS()
class BLACKBIRD_API ABlackbirdPlayerStart : public APlayerStart
{
	GENERATED_BODY()

public:
	ABlackbirdPlayerStart(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	ABlackbirdTrack* GetTrack() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Track")
	TObjectPtr<ABlackbirdTrack> Track;
};
