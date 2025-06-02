// Copyright Alien Shores 2025


#include "UI/Widget/Cursor/BlackbirdCursorWidget.h"

#include "UI/BlackbirdHUD.h"

ABlackbirdHUD* UBlackbirdCursorWidget::GetHUD() const
{
	return Cast<ABlackbirdHUD>(GetOwningPlayer()->GetHUD());
}

UMVVM_PlayerTargeting* UBlackbirdCursorWidget::GetPlayerTargetingViewModel() const
{
	return GetHUD()->GetPlayerTargetingViewModel();
}
