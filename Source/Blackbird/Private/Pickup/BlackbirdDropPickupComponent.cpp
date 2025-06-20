// Copyright Alien Shores 2025


#include "Pickup/BlackbirdDropPickupComponent.h"

#include "Pickup/BlackbirdPickup.h"
#include "Utils/ArrayUtils.h"

bool FBlackbirdDropDefinition::RollForDrop() const
{
	if (DropType == EBlackbirdDropType::ChanceToDrop)
	{
		return FMath::RandRange(0.f, 1.f) <= DropChance;
	}
	return true;
}

UBlackbirdDropPickupComponent::UBlackbirdDropPickupComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

TArray<ABlackbirdPickup*> UBlackbirdDropPickupComponent::Drop() const
{
	TArray<ABlackbirdPickup*> Drops;
	for (const FBlackbirdDropDefinition& DropDef : DropClasses)
	{
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
