// Copyright Alien Shores 2025


#include "UI/BlackbirdHUD.h"

#include "Player/BlackbirdPlayerShip.h"
#include "Ship/BlackbirdShip.h"
#include "UI/ViewModel/MVVM_PlayerTargeting.h"
#include "UI/ViewModel/MVVM_ShipAttributes.h"
#include "UI/Widget/HUD/BlackbirdGameHUDWidget.h"

UMVVM_ShipAttributes* ABlackbirdHUD::GetShipAttributesViewModel() const
{
	return ShipAttributesViewModel;
}

UMVVM_PlayerTargeting* ABlackbirdHUD::GetPlayerTargetingViewModel() const
{
	return PlayerTargetingViewModel;
}

void ABlackbirdHUD::BeginPlay()
{
	Super::BeginPlay();
	checkf(ShipAttributesViewModelClass, TEXT("[%s] ShipAttributesViewModelClass must be specified"), *GetName());
	checkf(PlayerTargetingViewModelClass, TEXT("[%s] PlayerTargetingViewModelClass must be specified"), *GetName());
	checkf(GameHUDWidgetClass, TEXT("[%s] GameHUDWidgetClass must be specified"), *GetName());
	ShipAttributesViewModel = NewObject<UMVVM_ShipAttributes>(this, ShipAttributesViewModelClass);
	PlayerTargetingViewModel = NewObject<UMVVM_PlayerTargeting>(this, PlayerTargetingViewModelClass);
	GameHUDWidget = CreateWidget<UBlackbirdGameHUDWidget>(GetWorld(), GameHUDWidgetClass);
	GameHUDWidget->AddToViewport();
	if (ABlackbirdShip* PlayerShip = Cast<ABlackbirdShip>(GetOwningPawn()))
	{
		if (PlayerShip->IsAbilitySystemReady())
		{
			OnAbilitySystemReady(PlayerShip->GetBlackbirdAbilitySystemComponent());
		}
		else
		{
			PlayerShip->OnAbilitySystemReadyDelegate.AddDynamic(this, &ABlackbirdHUD::OnAbilitySystemReady);
		}
	}
}

void ABlackbirdHUD::OnAbilitySystemReady(UBlackbirdAbilitySystemComponent* BlackbirdAbilitySystemComponent)
{
	if (const ABlackbirdShip* PlayerShip = Cast<ABlackbirdShip>(GetOwningPawn()))
	{
		ShipAttributesViewModel->BindDependencies(PlayerShip);
	}
	if (const ABlackbirdPlayerShip* PlayerShip = Cast<ABlackbirdPlayerShip>(GetOwningPawn()))
	{
		PlayerTargetingViewModel->BindDependencies(PlayerShip);
	}
}
