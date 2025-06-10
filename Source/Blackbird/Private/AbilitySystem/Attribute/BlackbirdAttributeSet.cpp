// Copyright Alien Shores 2025


#include "AbilitySystem/Attribute/BlackbirdAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "AbilitySystem/BlackbirdAbilitySystemLibrary.h"
#include "AbilitySystem/Attribute/BlackbirdAttributeTags.h"
#include "AbilitySystem/Attribute/BlackbirdLevelUpAttributeValue.h"
#include "Net/UnrealNetwork.h"

UBlackbirdAttributeSet::UBlackbirdAttributeSet()
{
	FBlackbirdAttributeTags AttributeTags = FBlackbirdAttributeTags::Get();
	InitializeMapsForAttributeAndTag(AttributeTags.Attributes_Meta_IncomingXP, GetMeta_IncomingXPAttribute);
	InitializeMapsForAttributeAndTag(AttributeTags.Attributes_Primary_CriticalChance, GetCriticalChanceAttribute);
	InitializeMapsForAttributeAndTag(AttributeTags.Attributes_Primary_Defense, GetDefenseAttribute);
	InitializeMapsForAttributeAndTag(AttributeTags.Attributes_Primary_MaxEnergy, GetMaxEnergyAttribute);
	InitializeMapsForAttributeAndTag(AttributeTags.Attributes_Primary_MaxHeat, GetMaxHeatAttribute);
	InitializeMapsForAttributeAndTag(AttributeTags.Attributes_Primary_Strength, GetStrengthAttribute);
	InitializeMapsForAttributeAndTag(AttributeTags.Attributes_Vital_Energy, GetEnergyAttribute);
	InitializeMapsForAttributeAndTag(AttributeTags.Attributes_Vital_AvailableHeat, GetAvailableHeatAttribute);
	InitializeMapsForAttributeAndTag(AttributeTags.Attributes_Primary_HeatCooldown, GetHeatCooldownAttribute);
}

void UBlackbirdAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	// primary attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UBlackbirdAttributeSet, MaxEnergy, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBlackbirdAttributeSet, MaxHeat, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBlackbirdAttributeSet, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBlackbirdAttributeSet, Defense, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBlackbirdAttributeSet, CriticalChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBlackbirdAttributeSet, HeatCooldown, COND_None, REPNOTIFY_Always);
	// vital attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UBlackbirdAttributeSet, AvailableHeat, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBlackbirdAttributeSet, Energy, COND_None, REPNOTIFY_Always);
}

void UBlackbirdAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	if (Attribute == GetEnergyAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0, GetMaxEnergy());
	}
	else if (Attribute == GetAvailableHeatAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0, GetMaxHeat());
	}
}

void UBlackbirdAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
	if (Attribute == GetMaxEnergyAttribute() && bResetEnergy)
	{
		SetEnergy(GetMaxEnergy());
		bResetEnergy = false;
	}
	if (Attribute == GetMaxHeatAttribute() && bResetAvailableHeat)
	{
		SetAvailableHeat(GetMaxHeat());
		bResetAvailableHeat = false;
	}
}

void UBlackbirdAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	if (UBlackbirdAbilitySystemLibrary::IsDead(UBlackbirdAbilitySystemLibrary::GetEffectTargetAvatarActor(Data)))
	{
		// Do not do anything for dead targets 
		return;
	}
	if (Data.EvaluatedData.Attribute == GetEnergyAttribute())
	{
		SetEnergy(FMath::Clamp(GetEnergy(), 0.f, GetMaxEnergy()));
	}
	else if (Data.EvaluatedData.Attribute == GetAvailableHeatAttribute())
	{
		SetAvailableHeat(FMath::Clamp(GetAvailableHeat(), 0.f, GetMaxHeat()));
	}
	else if (Data.EvaluatedData.Attribute == GetMeta_IncomingXPAttribute())
	{
		HandleIncomingXP(Data);
	}
}

void UBlackbirdAttributeSet::LevelUp(TArray<FBlackbirdLevelUpAttributeValue> LevelUpAttributeValues)
{
	bResetHealth = true;
	bResetEnergy = true;
	bResetAvailableHeat = true;
	for (const FBlackbirdLevelUpAttributeValue& AttributeValue : LevelUpAttributeValues)
	{
		float NewValue = AttributeValue.Value;
		const FGameplayAttribute& Attribute = AttributesByTag[AttributeValue.AttributeTag]();
		Attribute.SetNumericValueChecked(NewValue, this);
	}
}

void UBlackbirdAttributeSet::HandleIncomingXP(const FGameplayEffectModCallbackData& Data)
{
	const float IncomingXP = GetMeta_IncomingXP();
	SetMeta_IncomingXP(0);
	OnReceivedXP.Broadcast(IncomingXP);
}
