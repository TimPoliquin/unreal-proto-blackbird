// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "BlackbirdAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class BLACKBIRD_API UBlackbirdAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	static UBlackbirdAssetManager& Get();

protected:
	virtual void StartInitialLoading() override;
};
