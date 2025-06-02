// Copyright Alien Shores

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"

#include "TargetDataUnderMouse.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
	FMouseTargetDataSignature,
	const FGameplayAbilityTargetDataHandle&,
	DataHandle
);

/**
 * 
 */
UCLASS()
class BLACKBIRD_API UTargetDataUnderMouse : public UAbilityTask
{
	GENERATED_BODY()

public:
	UFUNCTION(
		BlueprintCallable,
		Category = "Ability|Tasks",
		meta=(
			HidePin="OwningAbility",
			DefaultToSelf="OwningAbility",
			BlueprintInternalUseOnly = true,
			DisplayName="TargetDataUnderMouse"
		)
	)
	static UTargetDataUnderMouse* CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility, float TargetingDistance = 10000.f, bool bDebug = false);

	UPROPERTY(BlueprintAssignable)
	FMouseTargetDataSignature OnTargetAssigned;

protected:
	void OnTargetDataReplicatedCallback(
		const FGameplayAbilityTargetDataHandle& DataHandle,
		FGameplayTag GameplayTag
	) const;
	virtual void Activate() override;

private:
	void SendMouseCursorDataToServer() const;
	float TargetingDistance;
	bool bDebug;
};
