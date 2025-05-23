// Copyright Alien Shores 2025


#include "UI/BlackbirdHUD.h"

#include "Ship/BlackbirdShip.h"
#include "UI/ViewModel/MVVM_ShipAttributes.h"
#include "UI/Widget/PlayerShipAttributesWidget.h"

UMVVM_ShipAttributes* ABlackbirdHUD::GetShipAttributesViewModel()
{
	return ShipAttributesViewModel;
}

void ABlackbirdHUD::BeginPlay()
{
	Super::BeginPlay();
	checkf(ShipAttributesViewModelClass, TEXT("[%s] ShipAttributesViewModelClass must be specified"), *GetName());
	checkf(PlayerShipAttributesWidgetClass, TEXT("[%s] PlayerShipAttributesWidgetClass must be specified"), *GetName());

	ShipAttributesViewModel = NewObject<UMVVM_ShipAttributes>(this, ShipAttributesViewModelClass);
	if (ABlackbirdShip* PlayerShip = Cast<ABlackbirdShip>(GetOwningPawn()))
	{
		PlayerShip->OnAbilitySystemReadyDelegate.AddDynamic(this, &ABlackbirdHUD::OnAbilitySystemReady);
	}
	PlayerShipAttributesWidget = CreateWidget<UPlayerShipAttributesWidget>(GetWorld(), PlayerShipAttributesWidgetClass);
	PlayerShipAttributesWidget->AddToViewport();
}

void ABlackbirdHUD::OnAbilitySystemReady(UBlackbirdAbilitySystemComponent* BlackbirdAbilitySystemComponent)
{
	if (const ABlackbirdShip* PlayerShip = Cast<ABlackbirdShip>(GetOwningPawn()))
	{
		ShipAttributesViewModel->BindDependencies(PlayerShip);
	}
}
