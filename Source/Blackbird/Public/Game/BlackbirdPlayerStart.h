// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "BlackbirdPlayerStart.generated.h"

class ABlackbirdLevelTrack;

UCLASS()
class BLACKBIRD_API ABlackbirdPlayerStart : public APlayerStart
{
	GENERATED_BODY()

public:
	ABlackbirdPlayerStart(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	ABlackbirdLevelTrack* GetLevelTrack() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Track")
	TObjectPtr<ABlackbirdLevelTrack> LevelTrack;
};
