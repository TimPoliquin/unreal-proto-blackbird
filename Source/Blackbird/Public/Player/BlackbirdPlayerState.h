// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "BlackbirdPlayerState.generated.h"

class UBlackbirdAbilitySystemComponent;
class UAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class BLACKBIRD_API ABlackbirdPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	ABlackbirdPlayerState();
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	UBlackbirdAbilitySystemComponent* GetBlackbirdAbilitySystemComponent();
private:
	UPROPERTY()
	TObjectPtr<UBlackbirdAbilitySystemComponent> BlackbirdAbilitySystemComponent;
};
