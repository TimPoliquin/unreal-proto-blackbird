// Copyright Alien Shores 2025


#include "Targeting/TargetableInterface.h"


// Add default functionality here for any ITargetableInterface functions that are not pure virtual.
void ITargetableInterface::Mark(AActor* ToMark)
{
	if (IsValid(ToMark) && ToMark->Implements<UTargetableInterface>())
	{
		Execute_Mark(ToMark);
	}
}

void ITargetableInterface::Unmark(AActor* ToUnmark)
{
	if (IsValid(ToUnmark) && ToUnmark->Implements<UTargetableInterface>())
	{
		Execute_Unmark(ToUnmark);
	}
}

bool ITargetableInterface::IsTargetable(const AActor* ToCheck)
{
	return IsValid(ToCheck) && ToCheck->Implements<UTargetableInterface>();
}
