// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "MVVMViewModelBase.h"
#include "GameplayTagContainer.h"
#include "MVVM_Attributes.generated.h"

struct FGameplayTag;
class UBlackbirdAttributeSet;
class ABlackbirdCharacter;
/**
 * 
 */
UCLASS()
class BLACKBIRD_API UMVVM_Attributes : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	UMVVM_Attributes();

	UFUNCTION(BlueprintCallable)
	void BindDependencies(const ABlackbirdCharacter* Owner);
	float GetHealth() const;
	void SetHealth(const float InHealth);
	float GetMaxHealth() const;
	void SetMaxHealth(const float InMaxHealth);
	float GetEnergy() const;
	void SetEnergy(const float InEnergy);
	float GetMaxEnergy() const;
	void SetMaxEnergy(const float InMaxEnergy);
	float GetAvailableHeat() const;
	void SetAvailableHeat(const float InHeat);
	float GetMaxHeat() const;
	void SetMaxHeat(const float InMaxHeat);
	UFUNCTION(BlueprintCallable, BlueprintPure, FieldNotify)
	float GetHealthPercentage() const;
	UFUNCTION(BlueprintCallable, BlueprintPure, FieldNotify)
	float GetEnergyPercentage() const;
	UFUNCTION(BlueprintCallable, BlueprintPure, FieldNotify)
	float GetHeatPercentage() const;
	UFUNCTION(BlueprintCallable, BlueprintPure, FieldNotify)
	float GetHeatAmount() const;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Getter, Setter, FieldNotify)
	float Health;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Getter, Setter, FieldNotify)
	float MaxHealth;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Getter, Setter, FieldNotify)
	float Energy;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Getter, Setter, FieldNotify)
	float MaxEnergy;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Getter, Setter, FieldNotify)
	float AvailableHeat;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Getter, Setter, FieldNotify)
	float MaxHeat;

private:
	UFUNCTION()
	void OnReceivedDamage(const float DamageAmount, const bool bFatal);
	void AddTagToAttributeSetterMap(
		const FGameplayTag& Tag,
		TFunction<void(UMVVM_Attributes*, const float)> Setter
	);
	void InitializeValues(const ABlackbirdCharacter* Owner, const UBlackbirdAttributeSet* AttributeSet);

	TMap<FGameplayTag, TFunction<void(const float)>> TagToAttributeSetterMap;
};
