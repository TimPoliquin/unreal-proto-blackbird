// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/BlackbirdGameModeBase.h"

#include "Game/BlackbirdPlayerStart.h"
#include "Player/BlackbirdPlayerController.h"

void ABlackbirdGameModeBase::InitStartSpot_Implementation(AActor* StartSpot, AController* NewPlayer)
{
	Super::InitStartSpot_Implementation(StartSpot, NewPlayer);
	if (const ABlackbirdPlayerStart* PlayerStart = Cast<const ABlackbirdPlayerStart>(StartSpot))
	{
		if (ABlackbirdPlayerController* PlayerController = Cast<ABlackbirdPlayerController>(NewPlayer))
		{
			PlayerController->SetLevelTrack(PlayerStart->GetLevelTrack());
		}
	}
}
