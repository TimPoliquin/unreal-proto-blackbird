// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

struct FBlackbirdTrackTags
{
	FGameplayTag Track;
	FGameplayTag Track_Event;
	FGameplayTag Track_Event_Start;
	FGameplayTag Track_Event_End;

	static FBlackbirdTrackTags& Get()
	{
		if (!Instance.bInitialized)
		{
			Initialize();
		}
		return Instance;
	}

	static void Initialize();
	static bool IsTrackTag(const FGameplayTag& Tag);

private:
	bool bInitialized = false;
	static FBlackbirdTrackTags Instance;
};
