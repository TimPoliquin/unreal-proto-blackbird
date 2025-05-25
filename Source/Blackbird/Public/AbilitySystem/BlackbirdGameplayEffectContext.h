// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "BlackbirdGameplayEffectContext.generated.h"

USTRUCT(BlueprintType)
struct FBlackbirdGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()

	virtual UScriptStruct* GetScriptStruct() const override
	{
		return StaticStruct();
	}

	virtual bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess) override;

	bool IsCriticalHit() const
	{
		return bIsCriticalHit;
	}

	void SetIsCriticalHit(const bool bIn)
	{
		bIsCriticalHit = bIn;
	}

	bool IsBlockedHit() const
	{
		return bIsBlockedHit;
	}

	void SetIsBlockedHit(const bool bIn)
	{
		this->bIsBlockedHit = bIn;
	}

	FVector GetDeathImpulse() const
	{
		return DeathImpulse;
	}

	void SetDeathImpulse(const FVector& InDeathImpulse)
	{
		DeathImpulse = InDeathImpulse;
	}

	FVector GetKnockbackVector() const
	{
		return KnockbackVector;
	}

	void SetKnockbackVector(const FVector& InKnockbackVector)
	{
		KnockbackVector = InKnockbackVector;
	}

	bool IsRadialDamage() const
	{
		return bIsRadialDamage;
	}

	void SetIsRadialDamage(const bool InIsRadialDamage)
	{
		bIsRadialDamage = InIsRadialDamage;
	}

	float GetRadialDamageInnerRadius() const
	{
		return RadialDamageInnerRadius;
	}

	void SetRadialDamageInnerRadius(const float InRadialDamageInnerRadius)
	{
		this->RadialDamageInnerRadius = InRadialDamageInnerRadius;
	}

	float GetRadialDamageOuterRadius() const
	{
		return RadialDamageOuterRadius;
	}

	void SetRadialDamageOuterRadius(const float InRadialDamageOuterRadius)
	{
		this->RadialDamageOuterRadius = InRadialDamageOuterRadius;
	}

	FVector GetRadialDamageOrigin() const
	{
		return RadialDamageOrigin;
	}

	void SetRadialDamageOrigin(const FVector& InRadialDamageOrigin)
	{
		this->RadialDamageOrigin = InRadialDamageOrigin;
	}

	/** Creates a copy of this context, used to duplicate for later modifications */
	virtual FBlackbirdGameplayEffectContext* Duplicate() const override
	{
		FBlackbirdGameplayEffectContext* NewContext = new FBlackbirdGameplayEffectContext();
		*NewContext = *this;
		if (GetHitResult())
		{
			// Does a deep copy of the hit result
			NewContext->AddHitResult(*GetHitResult(), true);
		}
		return NewContext;
	}

protected:
	UPROPERTY()
	bool bIsBlockedHit = false;
	UPROPERTY()
	bool bIsCriticalHit = false;
	UPROPERTY()
	FVector DeathImpulse = FVector::ZeroVector;
	UPROPERTY()
	FVector KnockbackVector = FVector::ZeroVector;
	UPROPERTY()
	bool bIsRadialDamage = false;


	UPROPERTY()
	float RadialDamageInnerRadius = 0.f;
	UPROPERTY()
	float RadialDamageOuterRadius = 0.f;
	UPROPERTY()
	FVector RadialDamageOrigin = FVector::ZeroVector;

private:
	void GetSavingBits(uint32& RepBits) const;
	void AssignValuesToArchive(FArchive& Ar, UPackageMap* Map, const uint32& RepBits, bool& bOutSuccess);
};

template <>
struct TStructOpsTypeTraits<
		FBlackbirdGameplayEffectContext> : TStructOpsTypeTraitsBase2<FBlackbirdGameplayEffectContext>
{
	enum
	{
		WithNetSerializer = true,
		WithCopy = true,
	};
};
