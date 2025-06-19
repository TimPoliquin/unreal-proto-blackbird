#pragma once
#include "GameplayTagContainer.h"

struct FBlackbirdAbilitySystemTags
{
	FGameplayTag Abilities;
	FGameplayTag Abilities_Ability;
	FGameplayTag Abilities_Ability_BasicAttack;
	FGameplayTag Abilities_Ability_Repel;
	FGameplayTag Abilities_Ability_Shield;
	FGameplayTag Abilities_Ability_VentHeat;
	FGameplayTag Abilities_Status;
	FGameplayTag Abilities_Status_Unavailable;
	FGameplayTag Abilities_Status_Available;
	FGameplayTag Abilities_Status_Equipped;
	FGameplayTag Abilities_Type;
	FGameplayTag Abilities_Type_Active;
	FGameplayTag Abilities_Type_Passive;
	FGameplayTag Abilities_Effect;
	FGameplayTag Abilities_Effect_Overheated;
	FGameplayTag Abilities_Effect_Repel;
	FGameplayTag Abilities_Effect_Shielded;
	FGameplayTag Abilities_Effect_Venting;
	FGameplayTag Abilities_Effect_Magnitude;

	static FBlackbirdAbilitySystemTags& Get()
	{
		if (!Instance.bInitialized)
		{
			Initialize();
		}
		return Instance;
	}

	static void Initialize();
	static bool IsAbilitiesTag(const FGameplayTag& Tag);

private:
	bool bInitialized = false;
	static FBlackbirdAbilitySystemTags Instance;
};
