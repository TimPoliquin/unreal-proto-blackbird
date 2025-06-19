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
	Instance.Abilities_Ability_Repel = TagManager.AddNativeGameplayTag(FName("Abilities.Ability.Repel"));
	Instance.Abilities_Ability_Shield = TagManager.AddNativeGameplayTag(FName("Abilities.Ability.Shield"));
	Instance.Abilities_Ability_VentHeat = TagManager.AddNativeGameplayTag(FName("Abilities.Ability.VentHeat"));
	Instance.Abilities_Status = TagManager.AddNativeGameplayTag(FName("Abilities.Status"));
	Instance.Abilities_Status_Unavailable = TagManager.AddNativeGameplayTag(FName("Abilities.Status.Unavailable"));
	Instance.Abilities_Status_Available = TagManager.AddNativeGameplayTag(FName("Abilities.Status.Available"));
	Instance.Abilities_Status_Equipped = TagManager.AddNativeGameplayTag(FName("Abilities.Status.Equipped"));
	Instance.Abilities_Type = TagManager.AddNativeGameplayTag(FName("Abilities.Type"));
	Instance.Abilities_Type_Active = TagManager.AddNativeGameplayTag(FName("Abilities.Type.Active"));
	Instance.Abilities_Type_Passive = TagManager.AddNativeGameplayTag(FName("Abilities.Type.Passive"));
	Instance.Abilities_Effect = TagManager.AddNativeGameplayTag(FName("Abilities.Effect"));
	Instance.Abilities_Effect_Overheated = TagManager.AddNativeGameplayTag(FName("Abilities.Effect.Overheated"));
	Instance.Abilities_Effect_Shielded = TagManager.AddNativeGameplayTag(FName("Abilities.Effect.Shielded"));
	Instance.Abilities_Effect_Venting = TagManager.AddNativeGameplayTag(FName("Abilities.Effect.Venting"));
	Instance.Abilities_Effect_Magnitude = TagManager.AddNativeGameplayTag(FName("Abilities.Effect.Magnitude"));

	Instance.bInitialized = true;
}

bool FBlackbirdAbilitySystemTags::IsAbilitiesTag(const FGameplayTag& Tag)
{
	return Tag.MatchesTag(Instance.Abilities);
}
