// Copyright Alien Shores 2025


#include "UI/ViewModel/MVVM_PlayerTargeting.h"

#include "Player/BlackbirdPlayerCharacter.h"
#include "Player/PlayerTargetingComponent.h"

bool UMVVM_PlayerTargeting::GetHasTarget() const
{
	return HasTarget;
}

void UMVVM_PlayerTargeting::SetHasTarget(const bool InHasTarget)
{
	bool bFireEvent = InHasTarget != HasTarget;
	this->HasTarget = InHasTarget;
	if (bFireEvent)
	{
		if (InHasTarget)
		{
			OnTargetAcquired.Broadcast();
		}
		else
		{
			OnTargetLost.Broadcast();
		}
	}
}

void UMVVM_PlayerTargeting::BindDependencies(const ABlackbirdPlayerCharacter* PlayerCharacter)
{
	PlayerCharacter->GetTargetingComponent()->OnPlayerTargetingChangedDelegate.AddDynamic(
		this, &UMVVM_PlayerTargeting::OnPlayerTargetChanged);
}

void UMVVM_PlayerTargeting::OnPlayerTargetChanged(const AActor* Target, const ETargetingStatus& Status)
{
	SetHasTarget(Status == ETargetingStatus::TargetingEnemy);
}
