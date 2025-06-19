// Copyright Alien Shores 2025


#include "UI/Widget/Attributes/PlayerAttributesWidget.h"

#include "UI/BlackbirdHUD.h"

ABlackbirdHUD* UPlayerAttributesWidget::GetHUD() const
{
	return Cast<ABlackbirdHUD>(GetOwningPlayer()->GetHUD());
}

UMVVM_Attributes* UPlayerAttributesWidget::GetAttributesViewModel() const
{
	if (ABlackbirdHUD* HUD = GetHUD())
	{
		return HUD->GetAttributesViewModel();
	}
	return nullptr;
}
