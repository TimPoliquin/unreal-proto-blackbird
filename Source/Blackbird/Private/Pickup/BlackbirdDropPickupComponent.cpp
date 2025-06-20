// Copyright Alien Shores 2025


#include "Pickup/BlackbirdDropPickupComponent.h"

#include "Pickup/BlackbirdPickup.h"
#include "Utils/ArrayUtils.h"

bool FBlackbirdDropDefinition::RollForDrop() const
{
	return FMath::RandRange(0.f, 1.f) <= DropChance;
}

UBlackbirdDropPickupComponent::UBlackbirdDropPickupComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

TArray<ABlackbirdPickup*> UBlackbirdDropPickupComponent::Drop() const
{
	TArray<ABlackbirdPickup*> Drops;
	for (int32 Idx = 0; Idx < NumDrops; Idx++)
	{
		const FBlackbirdDropDefinition& DropDef = UArrayUtils::GetRandomElement(DropClasses);
		if (DropDef.RollForDrop())
		{
			ABlackbirdPickup* Drop = GetWorld()->SpawnActorDeferred<ABlackbirdPickup>(
				DropDef.DropClass, GetOwner()->GetActorTransform(), GetOwner(), nullptr,
				ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn
			);
			Drop->FinishSpawning(GetOwner()->GetActorTransform());
			Drops.Add(Drop);
		}
	}
	return Drops;
}
