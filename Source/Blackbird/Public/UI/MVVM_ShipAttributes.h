// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "MVVMViewModelBase.h"
#include "GameplayTagContainer.h"
#include "MVVM_ShipAttributes.generated.h"

struct FGameplayTag;
class UBlackbirdAttributeSet;
class ABlackbirdShip;
/**
 * 
 */
UCLASS()
class BLACKBIRD_API UMVVM_ShipAttributes : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	UMVVM_ShipAttributes();

	UFUNCTION(BlueprintCallable)
	void BindDependencies(const ABlackbirdShip* Owner);
	float GetHealth() const;
	void SetHealth(const float Health);
	float GetMaxHealth() const;
	void SetMaxHealth(const float InMaxHealth);
	float GetEnergy() const;
	void SetEnergy(const float InEnergy);
	float GetMaxEnergy() const;
	void SetMaxEnergy(const float InMaxEnergy);
	float GetHeat() const;
	void SetHeat(const float Heat);
	float GetMaxHeat() const;
	void SetMaxHeat(const float MaxHeat);

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
	float Heat;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Getter, Setter, FieldNotify)
	float MaxHeat;

private:
	UFUNCTION()
	void OnAttributeChanged(
		const FGameplayAttribute& Attribute,
		const FGameplayTag& AttributeTag,
		const float NewValue
	);
	UFUNCTION()
	void OnReceivedDamage(const float DamageAmount, const bool bFatal);
	void AddTagToAttributeSetterMap(
		const FGameplayTag& Tag,
		TFunction<void(UMVVM_ShipAttributes*, const float)> Setter
	);
	void InitializeValues(const ABlackbirdShip* Owner, const UBlackbirdAttributeSet* AttributeSet);

	TMap<FGameplayTag, TFunction<void(const float)>> TagToAttributeSetterMap;
};
