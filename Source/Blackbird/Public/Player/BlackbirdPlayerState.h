// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "BlackbirdPlayerState.generated.h"

class UBlackbirdAttributeSet;
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
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	UBlackbirdAbilitySystemComponent* GetBlackbirdAbilitySystemComponent();
	UBlackbirdAttributeSet* GetBlackbirdAttributeSet();

private:
	UPROPERTY()
	TObjectPtr<UBlackbirdAbilitySystemComponent> BlackbirdAbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UBlackbirdAttributeSet> BlackbirdAttributeSet;
};
