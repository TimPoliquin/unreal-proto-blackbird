// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/BlackbirdHUD.h"
#include "PlayerAttributesWidget.generated.h"

class UMVVM_Attributes;
/**
 * 
 */
UCLASS()
class BLACKBIRD_API UPlayerAttributesWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	ABlackbirdHUD* GetHUD() const;
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UMVVM_Attributes* GetAttributesViewModel() const;
};
