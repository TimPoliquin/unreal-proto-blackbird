// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BlackbirdHUD.generated.h"

class UBlackbirdGameHUDWidget;
class UMVVM_PlayerTargeting;
class UBlackbirdAbilitySystemComponent;
class UPlayerAttributesWidget;
class UMVVM_Attributes;
/**
 * 
 */
UCLASS()
class BLACKBIRD_API ABlackbirdHUD : public AHUD
{
	GENERATED_BODY()

public:
	UMVVM_Attributes* GetAttributesViewModel() const;
	UMVVM_PlayerTargeting* GetPlayerTargetingViewModel() const;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMVVM_Attributes> AttributesViewModelClass;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	TObjectPtr<UMVVM_Attributes> AttributesViewModel;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMVVM_PlayerTargeting> PlayerTargetingViewModelClass;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	TObjectPtr<UMVVM_PlayerTargeting> PlayerTargetingViewModel;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UBlackbirdGameHUDWidget> GameHUDWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UBlackbirdGameHUDWidget> GameHUDWidget;

private:
	UFUNCTION()
	void OnAbilitySystemReady(UBlackbirdAbilitySystemComponent* BlackbirdAbilitySystemComponent);
};
