// Copyright Alien Shores 2025


#include "AbilitySystem/Attribute/BlackbirdBasicAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "AbilitySystem/BlackbirdAbilitySystemLibrary.h"
#include "AbilitySystem/Attribute/BlackbirdAttributeTags.h"
#include "Net/UnrealNetwork.h"

UBlackbirdBasicAttributeSet::UBlackbirdBasicAttributeSet()
{
	FBlackbirdAttributeTags AttributeTags = FBlackbirdAttributeTags::Get();
	InitializeMapsForAttributeAndTag(AttributeTags.Attributes_Meta_IncomingDamage, GetMeta_IncomingDamageAttribute);
	InitializeMapsForAttributeAndTag(AttributeTags.Attributes_Primary_MaxHealth, GetMaxHealthAttribute);
	InitializeMapsForAttributeAndTag(AttributeTags.Attributes_Vital_Health, GetHealthAttribute);
}

bool UBlackbirdBasicAttributeSet::IsAlive() const
{
	return GetHealth() > 0;
}

bool UBlackbirdBasicAttributeSet::IsDead() const
{
	return GetHealth() <= 0;
}

void UBlackbirdBasicAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UBlackbirdBasicAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBlackbirdBasicAttributeSet, Health, COND_None, REPNOTIFY_Always);
}

void UBlackbirdBasicAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0, GetMaxHealth());
	}
}

void UBlackbirdBasicAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue,
                                                      float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
	if (Attribute == GetMaxHealthAttribute() && bResetHealth)
	{
		SetHealth(GetMaxHealth());
		bResetHealth = false;
	}
}

void UBlackbirdBasicAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	if (UBlackbirdAbilitySystemLibrary::IsDead(UBlackbirdAbilitySystemLibrary::GetEffectTargetAvatarActor(Data)))
	{
		// Do not do anything for dead targets 
		return;
	}
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}
	else if (Data.EvaluatedData.Attribute == GetMeta_IncomingDamageAttribute())
	{
		HandleIncomingDamage(Data);
	}
}

FGameplayAttribute UBlackbirdBasicAttributeSet::GetAttributeByTag(const FGameplayTag& AttributeTag) const
{
	return AttributesByTag[AttributeTag]();
}

void UBlackbirdBasicAttributeSet::HandleIncomingDamage(const FGameplayEffectModCallbackData& Data)
{
	const float IncomingDamage = GetMeta_IncomingDamage();
	SetMeta_IncomingDamage(0);
	if (IncomingDamage > 0.f)
	{
		const float NewHealth = GetHealth() - IncomingDamage;
		SetHealth(FMath::Clamp(NewHealth, 0.f, GetMaxHealth()));
		FOnReceivedDamagePayload OnReceivedDamagePayload;
		OnReceivedDamagePayload.bFatal = NewHealth <= 0;
		OnReceivedDamagePayload.DamageAmount = IncomingDamage;
		OnReceivedDamagePayload.DamagedBy = UBlackbirdAbilitySystemLibrary::GetEffectSourceAvatarActor(Data);
		OnReceivedDamage.Broadcast(OnReceivedDamagePayload);
	}
}

void UBlackbirdBasicAttributeSet::InitializeMapsForAttributeAndTag(const FGameplayTag& AttributeTag,
                                                                   TStaticFuncPtr<FGameplayAttribute()> AttributeGetter)
{
	AttributesByTag.Add(AttributeTag, AttributeGetter);
	TagsByAttribute.Add(AttributeGetter(), AttributeTag);
}
