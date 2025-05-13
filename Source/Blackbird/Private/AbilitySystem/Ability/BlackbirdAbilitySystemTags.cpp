
#include "AbilitySystem/Ability/BlackbirdAbilitySystemTags.h"

#include "GameplayTagsManager.h"

FBlackbirdAbilitySystemTags FBlackbirdAbilitySystemTags::Instance;

void FBlackbirdAbilitySystemTags::Initialize()
{
	if (Instance.bInitialized)
	{
		return;
	}
	UGameplayTagsManager& TagManager = UGameplayTagsManager::Get();
	Instance.Abilities = TagManager.AddNativeGameplayTag(FName("Abilities"));
	Instance.Abilities_Ability = TagManager.AddNativeGameplayTag(FName("Abilities.Ability"));
	Instance.Abilities_Ability_BasicAttack = TagManager.AddNativeGameplayTag(FName("Abilities.Ability.BasicAttack"));
	Instance.Abilities_Ability_Shield = TagManager.AddNativeGameplayTag(FName("Abilities.Ability.Shield"));
	Instance.Abilities_Status = TagManager.AddNativeGameplayTag(FName("Abilities.Status"));
	Instance.Abilities_Status_Unavailable= TagManager.AddNativeGameplayTag(FName("Abilities.Status.Unavailable"));
	Instance.Abilities_Status_Available = TagManager.AddNativeGameplayTag(FName("Abilities.Status.Available"));
	Instance.Abilities_Status_Equipped = TagManager.AddNativeGameplayTag(FName("Abilities.Status.Equipped"));
	Instance.Abilities_Type = TagManager.AddNativeGameplayTag(FName("Abilities.Type"));
	Instance.Abilities_Type_Active = TagManager.AddNativeGameplayTag(FName("Abilities.Type.Active"));
	Instance.Abilities_Type_Passive = TagManager.AddNativeGameplayTag(FName("Abilities.Type.Passive"));

	Instance.bInitialized = true;
}

bool FBlackbirdAbilitySystemTags::IsAbilitiesTag(const FGameplayTag& Tag)
{
	return Tag.MatchesTag(Instance.Abilities);
}
