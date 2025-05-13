#include "Input/BlackbirdInputTags.h"

#include "GameplayTagsManager.h"
#include "GameplayTagContainer.h"

FBlackbirdInputTags FBlackbirdInputTags::Instance;


bool FBlackbirdInputTags::IsInputTag(const FGameplayTag& Tag)
{
	return Tag.MatchesTag(Get().InputTag);
}

void FBlackbirdInputTags::Initialize()
{
	if (Instance.bInitialized)
	{
		return;
	}
	UGameplayTagsManager& TagManager = UGameplayTagsManager::Get();
	Instance.InputTag = TagManager.AddNativeGameplayTag(FName("InputTag"));
	Instance.InputTag_Move = TagManager.AddNativeGameplayTag(FName("InputTag.Move"));
	Instance.InputTag_Attack_Basic = TagManager.AddNativeGameplayTag(FName("InputTag.Attack.Basic"));
	Instance.InputTag_Support_Shield = TagManager.AddNativeGameplayTag(FName("InputTag.Support.Shield"));

	Instance.bInitialized = true;
}
