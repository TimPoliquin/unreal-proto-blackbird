// Copyright Alien Shores 2025


#include "Utils/ActorFunctionLibrary.h"

void UActorFunctionLibrary::DestroyActorHierarchy(AActor* Actor)
{
	if (!Actor)
	{
		return;
	}
	TArray<AActor*> AllChildren;
	Actor->GetAttachedActors(AllChildren, false, true);
	for (AActor* Child : AllChildren)
	{
		Child->Destroy();
	}
	Actor->Destroy();
}
