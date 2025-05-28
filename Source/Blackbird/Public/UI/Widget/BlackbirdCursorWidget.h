// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BlackbirdCursorWidget.generated.h"

class UMVVM_PlayerTargeting;
class ABlackbirdHUD;
/**
 * 
 */
UCLASS()
class BLACKBIRD_API UBlackbirdCursorWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	ABlackbirdHUD* GetHUD() const;
};
