#pragma once
#include "GameplayTagContainer.h"

struct FBlackbirdAttributeTags
{
	FGameplayTag Attributes;
	FGameplayTag Attributes_Primary;
	FGameplayTag Attributes_Primary_MaxHealth;
	FGameplayTag Attributes_Primary_MaxEnergy;
	FGameplayTag Attributes_Primary_MaxHeat;
	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Defense;
	FGameplayTag Attributes_Primary_HeatCooldown;
	FGameplayTag Attributes_Primary_CriticalChance;
	FGameplayTag Attributes_Vital;
	FGameplayTag Attributes_Vital_Health;
	FGameplayTag Attributes_Vital_Energy;
	FGameplayTag Attributes_Vital_AvailableHeat;
	FGameplayTag Attributes_Meta;
	FGameplayTag Attributes_Meta_IncomingDamage;
	FGameplayTag Attributes_Meta_IncomingXP;

	static FBlackbirdAttributeTags& Get()
	{
		if (!Instance.bInitialized)
		{
			Initialize();
		}
		return Instance;
	}

	static void Initialize();
	static bool IsAttributesTag(const FGameplayTag& Tag);

private:
	bool bInitialized = false;
	static FBlackbirdAttributeTags Instance;
};
