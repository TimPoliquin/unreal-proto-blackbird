// Copyright Alien Shores 2025


#include "Track/BlackbirdTrackTags.h"

#include "GameplayTagsManager.h"

FBlackbirdTrackTags FBlackbirdTrackTags::Instance;

void FBlackbirdTrackTags::Initialize()
{
	if (Instance.bInitialized)
	{
		return;
	}
	UGameplayTagsManager& TagManager = UGameplayTagsManager::Get();
	Instance.Track = TagManager.AddNativeGameplayTag(FName("Track"));
	Instance.Track_Event = TagManager.AddNativeGameplayTag(FName("Track.Event"));
	Instance.Track_Event_Start = TagManager.AddNativeGameplayTag(FName("Track.Event.Start"));
	Instance.Track_Event_End = TagManager.AddNativeGameplayTag(FName("Track.Event.End"));

	Instance.bInitialized = true;
}

bool FBlackbirdTrackTags::IsTrackTag(const FGameplayTag& Tag)
{
	return Tag.MatchesTag(Instance.Track);
}
