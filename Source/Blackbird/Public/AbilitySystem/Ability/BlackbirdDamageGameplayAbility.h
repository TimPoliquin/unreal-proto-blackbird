// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "BlackbirdGameplayAbility.h"
#include "AbilitySystem/Effect/BlackbirdDamageEffectParams.h"
#include "AbilitySystem/Heat/AbilityHeatCostInterface.h"
#include "BlackbirdDamageGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class BLACKBIRD_API UBlackbirdDamageGameplayAbility : public UBlackbirdGameplayAbility, public IAbilityHeatCostInterface
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintPure)
	FBlackbirdDamageEffectParams MakeDamageEffectParamsFromClassDefaults(
		AActor* TargetActor = nullptr,
		const FVector& RadialDamageOrigin = FVector::ZeroVector,
		const bool bOverrideKnockbackDirection = false,
		const FVector& InKnockbackDirectionOverride = FVector::ZeroVector,
		bool bOverrideDeathImpulse = false,
		const FVector& InDeathImpulseDirectionOverride = FVector::ZeroVector,
		bool bOverridePitch = false,
		float PitchOverride = 0.f
	) const;
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int32 GetDamageAtLevel(const int32 AbilityLevel) const;
	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetEnergyCost(const float InLevel = 1.f) const;
	virtual float GetHeatCost_Implementation(const float InLevel = 1.f) const override;
	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetCooldown(const float InLevel = 1.f) const;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	TSubclassOf<UGameplayEffect> DamageEffectClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	FBlackbirdDamageConfig DamageConfig;
};
