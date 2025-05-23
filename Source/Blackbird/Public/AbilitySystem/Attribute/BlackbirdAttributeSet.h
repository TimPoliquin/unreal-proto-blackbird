// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "BlackbirdAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
struct FBlackbirdLevelUpAttributeValue;

template <class T>
using TStaticFuncPtr = typename TBaseStaticDelegateInstance<T, FDefaultDelegateUserPolicy>::FFuncPtr;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnReceivedDamageSignature, const float, DamageAmount, const bool, bFatal);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReceivedXPSignature, const float, XPAmount);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(
	FOnAttributeChangedSignature,
	const FGameplayAttribute&,
	Attribute,
	const FGameplayTag&,
	AttributeTag,
	const float,
	NewValue
);

/**
 * 
 */
UCLASS()
class BLACKBIRD_API UBlackbirdAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UBlackbirdAttributeSet();

	ATTRIBUTE_ACCESSORS(UBlackbirdAttributeSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(UBlackbirdAttributeSet, MaxEnergy);
	ATTRIBUTE_ACCESSORS(UBlackbirdAttributeSet, MaxHeat);
	ATTRIBUTE_ACCESSORS(UBlackbirdAttributeSet, Strength);
	ATTRIBUTE_ACCESSORS(UBlackbirdAttributeSet, Defense);
	ATTRIBUTE_ACCESSORS(UBlackbirdAttributeSet, CriticalChance);
	ATTRIBUTE_ACCESSORS(UBlackbirdAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(UBlackbirdAttributeSet, Energy);
	ATTRIBUTE_ACCESSORS(UBlackbirdAttributeSet, AvailableHeat);
	ATTRIBUTE_ACCESSORS(UBlackbirdAttributeSet, Meta_IncomingDamage);
	ATTRIBUTE_ACCESSORS(UBlackbirdAttributeSet, Meta_IncomingXP);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	bool IsAlive() const;
	bool IsDead() const;

	void LevelUp(TArray<FBlackbirdLevelUpAttributeValue> LevelUpAttributeValues);

	FOnReceivedDamageSignature OnReceivedDamage;
	FOnReceivedXPSignature OnReceivedXP;
	FOnAttributeChangedSignature OnAttributeChanged;

protected:
	/** Primary Attributes **/
	// Max Health
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Vital Attributes")
	FGameplayAttributeData MaxHealth;

	UFUNCTION()
	FORCEINLINE void OnRep_MaxHealth(const FGameplayAttributeData& OldValue) const
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UBlackbirdAttributeSet, MaxHealth, OldValue);
	}

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

	// Critical Chance - multiplier for chance to deal double damage
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalChance, Category = "Vital Attributes")
	FGameplayAttributeData CriticalChance;
	UFUNCTION()
	FORCEINLINE void OnRep_CriticalChance(const FGameplayAttributeData& OldValue) const
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UBlackbirdAttributeSet, CriticalChance, OldValue);
	}

	/** Dynamic Attributes **/
	// Health - how much damage the owner can take before being destroyed
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Dynamic Attributes")
	FGameplayAttributeData Health;
	UFUNCTION()
	FORCEINLINE void OnRep_Health(const FGameplayAttributeData& OldValue) const
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UBlackbirdAttributeSet, Health, OldValue);
	}

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
	// IncomingDamage - used to track and modify incoming damage
	UPROPERTY(BlueprintReadOnly, Category="Meta Attributes")
	FGameplayAttributeData Meta_IncomingDamage;
	// IncomingXP - used to track incoming xp
	UPROPERTY(BlueprintReadOnly, Category="Meta Attributes")
	FGameplayAttributeData Meta_IncomingXP;

private:
	void HandleIncomingDamage(const FGameplayEffectModCallbackData& Data);
	void HandleIncomingXP(const FGameplayEffectModCallbackData& Data);
	void InitializeMapsForAttributeAndTag(
		const FGameplayTag& AttributeTag,
		TStaticFuncPtr<FGameplayAttribute()> AttributeGetter
	);

	TMap<FGameplayTag, TStaticFuncPtr<FGameplayAttribute()>> AttributesByTag;
	TMap<FGameplayAttribute, FGameplayTag> TagsByAttribute;

	bool bResetHealth = false;
	bool bResetEnergy = false;
	bool bResetAvailableHeat = false;
};
