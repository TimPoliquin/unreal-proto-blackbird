// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "BlackbirdAttributeSetTypes.h"
#include "AbilitySystemComponent.h"
#include "BlackbirdBasicAttributeSet.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class BLACKBIRD_API UBlackbirdBasicAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UBlackbirdBasicAttributeSet();
	ATTRIBUTE_ACCESSORS(UBlackbirdBasicAttributeSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(UBlackbirdBasicAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(UBlackbirdBasicAttributeSet, Meta_IncomingDamage);

	bool IsAlive() const;
	bool IsDead() const;

	UPROPERTY(BlueprintAssignable)
	FOnReceivedDamageSignature OnReceivedDamage;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	FGameplayAttribute GetAttributeByTag(const FGameplayTag& AttributeTag) const;

	// Max Health
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Vital Attributes")
	FGameplayAttributeData MaxHealth;

	UFUNCTION()
	FORCEINLINE void OnRep_MaxHealth(const FGameplayAttributeData& OldValue) const
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UBlackbirdBasicAttributeSet, MaxHealth, OldValue);
	}

	// Health - how much damage the owner can take before being destroyed
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Dynamic Attributes")
	FGameplayAttributeData Health;
	UFUNCTION()
	FORCEINLINE void OnRep_Health(const FGameplayAttributeData& OldValue) const
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UBlackbirdBasicAttributeSet, Health, OldValue);
	}

	// IncomingDamage - used to track and modify incoming damage
	UPROPERTY(BlueprintReadOnly, Category="Meta Attributes")
	FGameplayAttributeData Meta_IncomingDamage;

protected:
	void HandleIncomingDamage(const FGameplayEffectModCallbackData& Data);

	void InitializeMapsForAttributeAndTag(
		const FGameplayTag& AttributeTag,
		TStaticFuncPtr<FGameplayAttribute()> AttributeGetter
	);

	bool bResetHealth = false;
	TMap<FGameplayTag, TStaticFuncPtr<FGameplayAttribute()>> AttributesByTag;
	TMap<FGameplayAttribute, FGameplayTag> TagsByAttribute;
};
