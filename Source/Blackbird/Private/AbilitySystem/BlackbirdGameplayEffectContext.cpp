﻿// Copyright Alien Shores 2025


#include "AbilitySystem/BlackbirdGameplayEffectContext.h"


bool FBlackbirdGameplayEffectContext::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
	uint32 RepBits = 0;
	if (Ar.IsSaving())
	{
		GetSavingBits(RepBits);
	}
	Ar.SerializeBits(&RepBits, 14);
	AssignValuesToArchive(Ar, Map, RepBits, bOutSuccess);
	if (Ar.IsLoading())
	{
		AddInstigator(Instigator.Get(), EffectCauser.Get()); // Just to initialize InstigatorAbilitySystemComponent
	}
	bOutSuccess = true;
	return true;
}

void FBlackbirdGameplayEffectContext::GetSavingBits(uint32& RepBits) const
{
	if (bReplicateInstigator && Instigator.IsValid())
	{
		RepBits |= 1 << 0;
	}
	if (bReplicateEffectCauser && EffectCauser.IsValid())
	{
		RepBits |= 1 << 1;
	}
	if (AbilityCDO.IsValid())
	{
		RepBits |= 1 << 2;
	}
	if (bReplicateSourceObject && SourceObject.IsValid())
	{
		RepBits |= 1 << 3;
	}
	if (Actors.Num() > 0)
	{
		RepBits |= 1 << 4;
	}
	if (HitResult.IsValid())
	{
		RepBits |= 1 << 5;
	}
	if (bHasWorldOrigin)
	{
		RepBits |= 1 << 6;
	}
	if (bIsBlockedHit)
	{
		RepBits |= 1 << 7;
	}
	if (bIsCriticalHit)
	{
		RepBits |= 1 << 8;
	}
	if (!DeathImpulse.IsZero())
	{
		RepBits |= 1 << 9;
	}
	if (!KnockbackVector.IsZero())
	{
		RepBits |= 1 << 10;
	}
	if (bIsRadialDamage)
	{
		RepBits |= 1 << 11;
		if (RadialDamageInnerRadius > 0.f)
		{
			RepBits |= 1 << 12;
		}
		if (RadialDamageOuterRadius > 0.f)
		{
			RepBits |= 1 << 13;
		}
		if (RadialDamageOrigin.IsZero())
		{
			RepBits |= 1 << 14;
		}
	}
}

void FBlackbirdGameplayEffectContext::AssignValuesToArchive(
	FArchive& Ar,
	UPackageMap* Map,
	const uint32& RepBits,
	bool& bOutSuccess
)
{
	if (RepBits & (1 << 0))
	{
		Ar << Instigator;
	}
	if (RepBits & (1 << 1))
	{
		Ar << EffectCauser;
	}
	if (RepBits & (1 << 2))
	{
		Ar << AbilityCDO;
	}
	if (RepBits & (1 << 3))
	{
		Ar << SourceObject;
	}
	if (RepBits & (1 << 4))
	{
		SafeNetSerializeTArray_Default<31>(Ar, Actors);
	}
	if (RepBits & (1 << 5))
	{
		if (Ar.IsLoading())
		{
			if (!HitResult.IsValid())
			{
				HitResult = MakeShared<FHitResult>();
			}
		}
		HitResult->NetSerialize(Ar, Map, bOutSuccess);
	}
	if (RepBits & (1 << 6))
	{
		Ar << WorldOrigin;
		bHasWorldOrigin = true;
	}
	else
	{
		bHasWorldOrigin = false;
	}
	if (RepBits & (1 << 7))
	{
		Ar << bIsBlockedHit;
	}
	if (RepBits & (1 << 8))
	{
		Ar << bIsCriticalHit;
	}
	if (RepBits & (1 << 9))
	{
		DeathImpulse.NetSerialize(Ar, Map, bOutSuccess);
	}
	if (RepBits & (1 << 10))
	{
		KnockbackVector.NetSerialize(Ar, Map, bOutSuccess);
	}
	if (RepBits & (1 << 11))
	{
		Ar << bIsRadialDamage;
		if (RepBits & (1 << 12))
		{
			Ar << RadialDamageInnerRadius;
		}
		if (RepBits & (1 << 13))
		{
			Ar << RadialDamageOuterRadius;
		}
		if (RepBits & (1 << 14))
		{
			RadialDamageOrigin.NetSerialize(Ar, Map, bOutSuccess);
		}
	}
}
