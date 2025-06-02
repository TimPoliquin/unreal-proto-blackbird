// Copyright Alien Shores 2025


#include "UI/Widget/Attributes/PlayerShipAttributesWidget.h"

#include "UI/BlackbirdHUD.h"

ABlackbirdHUD* UPlayerShipAttributesWidget::GetHUD() const
{
	return Cast<ABlackbirdHUD>(GetOwningPlayer()->GetHUD());
}

UMVVM_ShipAttributes* UPlayerShipAttributesWidget::GetShipAttributesViewModel() const
{
	if (ABlackbirdHUD* HUD = GetHUD())
	{
		return HUD->GetShipAttributesViewModel();
	}
	return nullptr;
}
