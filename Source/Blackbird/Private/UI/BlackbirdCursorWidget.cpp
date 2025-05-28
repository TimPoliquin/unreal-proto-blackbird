// Copyright Alien Shores 2025


#include "UI/Widget/BlackbirdCursorWidget.h"

#include "UI/BlackbirdHUD.h"

ABlackbirdHUD* UBlackbirdCursorWidget::GetHUD() const
{
	return Cast<ABlackbirdHUD>(GetOwningPlayer()->GetHUD());
}
