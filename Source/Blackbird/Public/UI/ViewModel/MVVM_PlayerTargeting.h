// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "Player/PlayerTargetingComponent.h"
#include "MVVM_PlayerTargeting.generated.h"

class ABlackbirdPlayerShip;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerTargetingViewModelTargetChangedSignature);

/**
 * 
 */
UCLASS()
class BLACKBIRD_API UMVVM_PlayerTargeting : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	bool GetHasTarget() const;
	void SetHasTarget(const bool InHasTarget);

	void BindDependencies(const ABlackbirdPlayerShip* PlayerShip);

	UPROPERTY(BlueprintAssignable)
	FPlayerTargetingViewModelTargetChangedSignature OnTargetAcquired;
	UPROPERTY(BlueprintAssignable)
	FPlayerTargetingViewModelTargetChangedSignature OnTargetLost;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Getter, Setter, FieldNotify)
	bool HasTarget = false;

private:
	UFUNCTION()
	void OnPlayerTargetChanged(const AActor* Target, const ETargetingStatus& Status);
};
