// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackbirdAssetManager.h"

#include "AbilitySystem/Ability/BlackbirdAbilitySystemTags.h"
#include "Input/BlackbirdInputTags.h"

UBlackbirdAssetManager& UBlackbirdAssetManager::Get()
{
	return *Cast<UBlackbirdAssetManager>(GEngine->AssetManager);
}

void UBlackbirdAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	FBlackbirdInputTags::Initialize();
	FBlackbirdAbilitySystemTags::Initialize();
}
