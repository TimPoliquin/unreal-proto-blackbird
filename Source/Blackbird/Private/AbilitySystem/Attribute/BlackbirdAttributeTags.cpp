// Copyright Alien Shores 2025


#include "AbilitySystem/Attribute/BlackbirdAttributeTags.h"


#include "AbilitySystem/Ability/BlackbirdAbilitySystemTags.h"

#include "GameplayTagsManager.h"

FBlackbirdAttributeTags FBlackbirdAttributeTags::Instance;

void FBlackbirdAttributeTags::Initialize()
{
	if (Instance.bInitialized)
	{
		return;
	}
	UGameplayTagsManager& TagManager = UGameplayTagsManager::Get();
	Instance.Attributes = TagManager.AddNativeGameplayTag(FName("Attributes"));
	Instance.Attributes_Meta = TagManager.AddNativeGameplayTag(FName("Attributes.Meta"));
	Instance.Attributes_Meta_IncomingDamage = TagManager.AddNativeGameplayTag(FName("Attributes.Meta.IncomingDamage"));
	Instance.Attributes_Meta_IncomingXP = TagManager.AddNativeGameplayTag(FName("Attributes.Meta.IncomingXP"));
	Instance.Attributes_Primary = TagManager.AddNativeGameplayTag(FName("Attributes.Primary"));
	Instance.Attributes_Primary_CriticalChance = TagManager.AddNativeGameplayTag(
		FName("Attributes.Primary.CriticalChance")
	);
	Instance.Attributes_Primary_Defense = TagManager.AddNativeGameplayTag(FName("Attributes.Primary.Defense"));
	Instance.Attributes_Primary_HeatCooldown = TagManager.AddNativeGameplayTag(FName("Attributes.Primary.HeatCooldown"));
	Instance.Attributes_Primary_MaxEnergy = TagManager.AddNativeGameplayTag(FName("Attributes.Primary.MaxEnergy"));
	Instance.Attributes_Primary_MaxHealth = TagManager.AddNativeGameplayTag(FName("Attributes.Primary.MaxHealth"));
	Instance.Attributes_Primary_MaxHeat = TagManager.AddNativeGameplayTag(FName("Attributes.Primary.MaxHeat"));
	Instance.Attributes_Primary_Strength = TagManager.AddNativeGameplayTag(FName("Attributes.Primary.Strength"));
	Instance.Attributes_Vital = TagManager.AddNativeGameplayTag(FName("Attributes.Vital"));
	Instance.Attributes_Vital_Energy = TagManager.AddNativeGameplayTag(FName("Attributes.Vital.Energy"));
	Instance.Attributes_Vital_Health = TagManager.AddNativeGameplayTag(FName("Attributes.Vital.Health"));
	Instance.Attributes_Vital_AvailableHeat = TagManager.AddNativeGameplayTag(FName("Attributes.Vital.AvailableHeat"));
	Instance.bInitialized = true;
}

bool FBlackbirdAttributeTags::IsAttributesTag(const FGameplayTag& Tag)
{
	return Tag.MatchesTag(Instance.Attributes);
}
