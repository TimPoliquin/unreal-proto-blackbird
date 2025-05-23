// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BlackbirdHUD.generated.h"

class UBlackbirdAbilitySystemComponent;
class UPlayerShipAttributesWidget;
class UMVVM_ShipAttributes;
/**
 * 
 */
UCLASS()
class BLACKBIRD_API ABlackbirdHUD : public AHUD
{
	GENERATED_BODY()

public:
	UMVVM_ShipAttributes* GetShipAttributesViewModel();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMVVM_ShipAttributes> ShipAttributesViewModelClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UMVVM_ShipAttributes> ShipAttributesViewModel;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPlayerShipAttributesWidget> PlayerShipAttributesWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UPlayerShipAttributesWidget> PlayerShipAttributesWidget;

private:
	UFUNCTION()
	void OnAbilitySystemReady(UBlackbirdAbilitySystemComponent* BlackbirdAbilitySystemComponent);
};
