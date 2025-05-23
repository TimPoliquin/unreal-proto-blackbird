// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/BlackbirdHUD.h"
#include "PlayerShipAttributesWidget.generated.h"

class UMVVM_ShipAttributes;
/**
 * 
 */
UCLASS()
class BLACKBIRD_API UPlayerShipAttributesWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	ABlackbirdHUD* GetHUD() const;
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UMVVM_ShipAttributes* GetShipAttributesViewModel() const;
};
