// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackbirdAssetManager.h"

#include "AbilitySystemGlobals.h"
#include "AbilitySystem/Ability/BlackbirdAbilitySystemTags.h"
#include "AbilitySystem/Attribute/BlackbirdAttributeTags.h"
#include "Input/BlackbirdInputTags.h"
#include "Track/BlackbirdTrackTags.h"

UBlackbirdAssetManager& UBlackbirdAssetManager::Get()
{
	return *Cast<UBlackbirdAssetManager>(GEngine->AssetManager);
}

void UBlackbirdAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	FBlackbirdInputTags::Initialize();
	FBlackbirdAbilitySystemTags::Initialize();
	FBlackbirdAttributeTags::Initialize();
	FBlackbirdTrackTags::Initialize();
	// DEVNOTE: Required to use TargetData (TargetDataUnderMouse)
	UAbilitySystemGlobals::Get().InitGlobalData();
}
