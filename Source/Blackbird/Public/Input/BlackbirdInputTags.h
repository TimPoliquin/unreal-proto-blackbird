#pragma once
#include "GameplayTagContainer.h"

struct FBlackbirdInputTags
{
	FGameplayTag InputTag;
	FGameplayTag InputTag_Move;
	FGameplayTag InputTag_Attack_Basic;

	static FBlackbirdInputTags& Get()
	{
		if (!Instance.bInitialized)
		{
			Initialize();
		}
		return Instance;
	}

	static void Initialize();
	static bool IsInputTag(const FGameplayTag& Tag);

private:
	bool bInitialized = false;
	static FBlackbirdInputTags Instance;
};
