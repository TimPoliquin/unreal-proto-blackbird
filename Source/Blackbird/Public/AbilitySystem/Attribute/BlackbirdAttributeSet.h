// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "BlackbirdAttributeSetTypes.h"
#include "BlackbirdBasicAttributeSet.h"
#include "BlackbirdAttributeSet.generated.h"

struct FBlackbirdLevelUpAttributeValue;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReceivedXPSignature, const float, XPAmount);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbsorbedDamageSignature, const float, DamageAmount);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTriggerOverheatSignature);

/**
 * 
 */
UCLASS()
class BLACKBIRD_API UBlackbirdAttributeSet : public UBlackbirdBasicAttributeSet
{
	GENERATED_BODY()

public:
	UBlackbirdAttributeSet();

	ATTRIBUTE_ACCESSORS(UBlackbirdAttributeSet, MaxEnergy);
	ATTRIBUTE_ACCESSORS(UBlackbirdAttributeSet, MaxHeat);
	ATTRIBUTE_ACCESSORS(UBlackbirdAttributeSet, Strength);
	ATTRIBUTE_ACCESSORS(UBlackbirdAttributeSet, Defense);
	ATTRIBUTE_ACCESSORS(UBlackbirdAttributeSet, HeatCooldown);
	ATTRIBUTE_ACCESSORS(UBlackbirdAttributeSet, CriticalChance);
	ATTRIBUTE_ACCESSORS(UBlackbirdAttributeSet, Energy);
	ATTRIBUTE_ACCESSORS(UBlackbirdAttributeSet, AvailableHeat);
	ATTRIBUTE_ACCESSORS(UBlackbirdAttributeSet, Meta_IncomingDamage);
	ATTRIBUTE_ACCESSORS(UBlackbirdAttributeSet, Meta_IncomingXP);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	void LevelUp(TArray<FBlackbirdLevelUpAttributeValue> LevelUpAttributeValues);

	UPROPERTY(BlueprintAssignable)
	FOnReceivedXPSignature OnReceivedXP;
	UPROPERTY(BlueprintAssignable)
	FOnTriggerOverheatSignature OnTriggerOverheat;
	UPROPERTY(BlueprintAssignable)
	FOnAbsorbedDamageSignature OnAbsorbedDamage;

	/** Primary Attributes **/
	// Max Energy
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxEnergy, Category = "Vital Attributes")
	FGameplayAttributeData MaxEnergy;
	UFUNCTION()
	FORCEINLINE void OnRep_MaxEnergy(const FGameplayAttributeData& OldValue) const
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UBlackbirdAttributeSet, MaxEnergy, OldValue);
	}

	// Max Heat
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHeat, Category = "Vital Attributes")
	FGameplayAttributeData MaxHeat;
	UFUNCTION()
	FORCEINLINE void OnRep_MaxHeat(const FGameplayAttributeData& OldValue) const
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UBlackbirdAttributeSet, MaxHeat, OldValue);
	}

	// Strength - multiplier for base damage
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strength, Category = "Vital Attributes")
	FGameplayAttributeData Strength;
	UFUNCTION()
	FORCEINLINE void OnRep_Strength(const FGameplayAttributeData& OldValue) const
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UBlackbirdAttributeSet, Strength, OldValue);
	}

	// Defense - multiplier for base damage reduction
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Defense, Category = "Vital Attributes")
	FGameplayAttributeData Defense;
	UFUNCTION()
	FORCEINLINE void OnRep_Defense(const FGameplayAttributeData& OldValue) const
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UBlackbirdAttributeSet, Defense, OldValue);
	}

	// Heat Cooldown - amount of available heat to restore every cooldown cycle.
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HeatCooldown, Category = "Vital Attributes")
	FGameplayAttributeData HeatCooldown;
	UFUNCTION()
	FORCEINLINE void OnRep_HeatCooldown(const FGameplayAttributeData& OldValue) const
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UBlackbirdAttributeSet, HeatCooldown, OldValue);
	}

	// Critical Chance - multiplier for chance to deal double damage
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalChance, Category = "Vital Attributes")
	FGameplayAttributeData CriticalChance;
	UFUNCTION()
	FORCEINLINE void OnRep_CriticalChance(const FGameplayAttributeData& OldValue) const
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UBlackbirdAttributeSet, CriticalChance, OldValue);
	}

	/** Dynamic Attributes **/
	// Energy - available power to use special abilities 
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Energy, Category = "Dynamic Attributes")
	FGameplayAttributeData Energy;
	UFUNCTION()
	FORCEINLINE void OnRep_Energy(const FGameplayAttributeData& OldValue) const
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UBlackbirdAttributeSet, Energy, OldValue);
	}

	//  Heat - accumulated by attacking and using shields. dissipated by dodging and using melee attacks
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_AvailableHeat, Category = "Dynamic Attributes")
	FGameplayAttributeData AvailableHeat;
	UFUNCTION()
	FORCEINLINE void OnRep_AvailableHeat(const FGameplayAttributeData& OldValue) const
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UBlackbirdAttributeSet, AvailableHeat, OldValue);
	}

	/**
	 * Meta Attributes
	 */
	// IncomingXP - used to track incoming xp
	UPROPERTY(BlueprintReadOnly, Category="Meta Attributes")
	FGameplayAttributeData Meta_IncomingXP;

protected:
	virtual void HandleIncomingDamage(const FGameplayEffectModCallbackData& Data) override;
	void HandleIncomingDamageAsHeat(const FGameplayEffectModCallbackData& Data);

private:
	void HandleIncomingXP(const FGameplayEffectModCallbackData& Data);

	bool bResetEnergy = false;
	bool bResetAvailableHeat = false;
};
