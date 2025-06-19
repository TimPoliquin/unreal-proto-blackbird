// Copyright Alien Shores 2025


#include "AbilitySystem/BlackbirdAbilitySystemLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/Character.h"
#include "GameplayAbilitySpec.h"
#include "GameplayEffectExtension.h"
#include "Abilities/GameplayAbility.h"
#include "AbilitySystem/BlackbirdGameplayEffectContext.h"
#include "AbilitySystem/Ability/BlackbirdAbilitySystemTags.h"
#include "AbilitySystem/Attribute/BlackbirdAttributeTags.h"
#include "AbilitySystem/Damage/DamageableInterface.h"

FActiveGameplayEffectHandle UBlackbirdAbilitySystemLibrary::ApplyEffectToSelf(
	AActor* Actor,
	const TSubclassOf<UGameplayEffect> Effect,
	const int32 Level,
	const float Magnitude
)
{
	if (!IsValid(Actor))
	{
		return FActiveGameplayEffectHandle();
	}
	if (!Effect)
	{
		UE_LOG(
			LogTemp,
			Warning,
			TEXT("[UBlackbirdAbilitySystemLibrary::ApplyToSelf] No effect class provided for [%s]"),
			*Actor->GetName()
		)
		return FActiveGameplayEffectHandle();
	}
	if (UAbilitySystemComponent* AbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(
		Actor
	))
	{
		FGameplayEffectContextHandle EffectContextHandle = AbilitySystemComponent->MakeEffectContext();
		EffectContextHandle.AddSourceObject(Actor);
		const FGameplayEffectSpecHandle GameplayEffectSpec = AbilitySystemComponent->MakeOutgoingSpec(
			Effect,
			Level,
			EffectContextHandle
		);
		GameplayEffectSpec.Data->SetSetByCallerMagnitude(FBlackbirdAbilitySystemTags::Get().Abilities_Effect_Magnitude,
		                                                 Magnitude);
		return AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(
			*GameplayEffectSpec.Data.Get(),
			AbilitySystemComponent
		);
	}
	return FActiveGameplayEffectHandle();
}

FPredictionKey UBlackbirdAbilitySystemLibrary::GetPredictionKeyFromAbilitySpec(const FGameplayAbilitySpec& AbilitySpec)
{
	if (TArray<UGameplayAbility*> Instances = AbilitySpec.GetAbilityInstances(); Instances.Num() > 0)
	{
		const FGameplayAbilityActivationInfo& ActivationInfo = Instances.Last()->GetCurrentActivationInfoRef();
		return ActivationInfo.GetActivationPredictionKey();
	}
	return FPredictionKey();
}

FGameplayEffectContextHandle UBlackbirdAbilitySystemLibrary::GetEffectContextHandle(
	const FGameplayEffectModCallbackData& Data
)
{
	return Data.EffectSpec.GetContext();
}

UAbilitySystemComponent* UBlackbirdAbilitySystemLibrary::GetEffectSourceAbilitySystemComponent(
	const FGameplayEffectModCallbackData& Data
)
{
	return GetEffectContextHandle(Data).GetOriginalInstigatorAbilitySystemComponent();
}

AActor* UBlackbirdAbilitySystemLibrary::GetEffectSourceAvatarActor(
	const FGameplayEffectModCallbackData& Data
)
{
	if (const UAbilitySystemComponent* AbilitySystemComponent = GetEffectSourceAbilitySystemComponent(Data))
	{
		return AbilitySystemComponent->GetAvatarActor();
	}
	return nullptr;
}

ACharacter* UBlackbirdAbilitySystemLibrary::GetEffectSourceCharacter(const FGameplayEffectModCallbackData& Data)
{
	if (const AController* Controller = GetEffectSourceController(Data))
	{
		return Controller->GetCharacter();
	}
	return nullptr;
}

AController* UBlackbirdAbilitySystemLibrary::GetEffectSourceController(
	const FGameplayEffectModCallbackData& Data
)
{
	if (const UAbilitySystemComponent* AbilitySystemComponent = GetEffectSourceAbilitySystemComponent(Data))
	{
		if (APlayerController* PlayerController = AbilitySystemComponent->AbilityActorInfo->PlayerController.Get())
		{
			return PlayerController;
		}
		if (const APawn* SourcePawn = Cast<APawn>(AbilitySystemComponent->GetAvatarActor()))
		{
			return SourcePawn->GetController();
		}
	}
	return nullptr;
}

AActor* UBlackbirdAbilitySystemLibrary::GetEffectTargetAvatarActor(const FGameplayEffectModCallbackData& Data)
{
	return Data.Target.AbilityActorInfo->AvatarActor.Get();
}

AController* UBlackbirdAbilitySystemLibrary::GetEffectTargetController(const FGameplayEffectModCallbackData& Data)
{
	return Data.Target.AbilityActorInfo->PlayerController.Get();
}

ACharacter* UBlackbirdAbilitySystemLibrary::GetEffectTargetCharacter(const FGameplayEffectModCallbackData& Data)
{
	return Cast<ACharacter>(GetEffectTargetAvatarActor(Data));
}

UAbilitySystemComponent* UBlackbirdAbilitySystemLibrary::GetEffectTargetAbilitySystemComponent(
	const FGameplayEffectModCallbackData& Data
)
{
	return UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(
		GetEffectTargetAvatarActor(Data)
	);
}

bool UBlackbirdAbilitySystemLibrary::IsAlive(AActor* Actor)
{
	if (const IDamageableInterface* DamageableActor = Cast<IDamageableInterface>(Actor))
	{
		return DamageableActor->IsAlive();
	}
	return false;
}

bool UBlackbirdAbilitySystemLibrary::IsDead(AActor* Actor)
{
	if (const IDamageableInterface* DamageableActor = Cast<IDamageableInterface>(Actor))
	{
		return DamageableActor->IsDead();
	}
	return true;
}

bool UBlackbirdAbilitySystemLibrary::IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FBlackbirdGameplayEffectContext* BlackbirdEffectContext = static_cast<const
		FBlackbirdGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return BlackbirdEffectContext->IsBlockedHit();
	}
	return false;
}

void UBlackbirdAbilitySystemLibrary::SetIsBlockedHit(
	FGameplayEffectContextHandle& Context,
	const bool InIsBlocked
)
{
	if (FBlackbirdGameplayEffectContext* BlackbirdEffectContext = static_cast<FBlackbirdGameplayEffectContext*>(Context.
		Get()))
	{
		BlackbirdEffectContext->SetIsBlockedHit(InIsBlocked);
	}
}

bool UBlackbirdAbilitySystemLibrary::IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FBlackbirdGameplayEffectContext* BlackbirdEffectContext = static_cast<const
		FBlackbirdGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return BlackbirdEffectContext->IsCriticalHit();
	}
	return false;
}

void UBlackbirdAbilitySystemLibrary::SetIsCriticalHit(FGameplayEffectContextHandle& Context, bool InIsCriticalHit)
{
	if (FBlackbirdGameplayEffectContext* BlackbirdEffectContext = static_cast<FBlackbirdGameplayEffectContext*>(Context.
		Get()))
	{
		BlackbirdEffectContext->SetIsCriticalHit(InIsCriticalHit);
	}
}

bool UBlackbirdAbilitySystemLibrary::IsRadialDamage(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FBlackbirdGameplayEffectContext* BlackbirdEffectContext = static_cast<const
		FBlackbirdGameplayEffectContext*>(
		EffectContextHandle.Get()))
	{
		return BlackbirdEffectContext->IsRadialDamage();
	}
	return false;
}

float UBlackbirdAbilitySystemLibrary::GetRadialDamageInnerRadius(
	const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FBlackbirdGameplayEffectContext* BlackbirdEffectContext = static_cast<const
		FBlackbirdGameplayEffectContext*>(
		EffectContextHandle.Get()))
	{
		return BlackbirdEffectContext->GetRadialDamageInnerRadius();
	}
	return 0.f;
}

float UBlackbirdAbilitySystemLibrary::GetRadialDamageOuterRadius(
	const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FBlackbirdGameplayEffectContext* BlackbirdEffectContext = static_cast<const
		FBlackbirdGameplayEffectContext*>(
		EffectContextHandle.Get()))
	{
		return BlackbirdEffectContext->GetRadialDamageOuterRadius();
	}
	return 0.f;
}

FVector UBlackbirdAbilitySystemLibrary::GetRadialDamageOrigin(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FBlackbirdGameplayEffectContext* BlackbirdEffectContext = static_cast<const
		FBlackbirdGameplayEffectContext*>(
		EffectContextHandle.Get()))
	{
		return BlackbirdEffectContext->GetRadialDamageOrigin();
	}
	return FVector::ZeroVector;
}

void UBlackbirdAbilitySystemLibrary::SetIsRadialDamage(
	FGameplayEffectContextHandle& EffectContextHandle,
	const bool InIsRadialDamage
)
{
	if (FBlackbirdGameplayEffectContext* BlackbirdEffectContext = static_cast<FBlackbirdGameplayEffectContext*>(
		EffectContextHandle.Get()))
	{
		return BlackbirdEffectContext->SetIsRadialDamage(InIsRadialDamage);
	}
}

void UBlackbirdAbilitySystemLibrary::SetRadialDamageInnerRadius(
	FGameplayEffectContextHandle& EffectContextHandle,
	const float InRadialDamageInnerRadius
)
{
	if (FBlackbirdGameplayEffectContext* BlackbirdEffectContext = static_cast<FBlackbirdGameplayEffectContext*>(
		EffectContextHandle.Get()))
	{
		return BlackbirdEffectContext->SetRadialDamageInnerRadius(InRadialDamageInnerRadius);
	}
}

void UBlackbirdAbilitySystemLibrary::SetRadialDamageOuterRadius(
	FGameplayEffectContextHandle& EffectContextHandle,
	const float InRadialDamageOuterRadius
)
{
	if (FBlackbirdGameplayEffectContext* BlackbirdEffectContext = static_cast<FBlackbirdGameplayEffectContext*>(
		EffectContextHandle.Get()))
	{
		return BlackbirdEffectContext->SetRadialDamageOuterRadius(InRadialDamageOuterRadius);
	}
}

void UBlackbirdAbilitySystemLibrary::SetRadialDamageOrigin(
	FGameplayEffectContextHandle& EffectContextHandle,
	const FVector& InRadialDamageOrigin
)
{
	if (FBlackbirdGameplayEffectContext* BlackbirdEffectContext = static_cast<FBlackbirdGameplayEffectContext*>(
		EffectContextHandle.Get()))
	{
		return BlackbirdEffectContext->SetRadialDamageOrigin(InRadialDamageOrigin);
	}
}

FVector UBlackbirdAbilitySystemLibrary::GetDeathImpulse(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FBlackbirdGameplayEffectContext* AuraEffectContext = static_cast<const FBlackbirdGameplayEffectContext*>(
		EffectContextHandle.Get()))
	{
		return AuraEffectContext->GetDeathImpulse();
	}
	return FVector::ZeroVector;
}

void UBlackbirdAbilitySystemLibrary::SetDeathImpulse(FGameplayEffectContextHandle& EffectContextHandle,
                                                     const FVector& InDeathImpulse)
{
	if (FBlackbirdGameplayEffectContext* AuraEffectContext = static_cast<FBlackbirdGameplayEffectContext*>(
		EffectContextHandle.Get()))
	{
		AuraEffectContext->SetDeathImpulse(InDeathImpulse);
	}
}

FVector UBlackbirdAbilitySystemLibrary::GetKnockbackVector(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FBlackbirdGameplayEffectContext* AuraEffectContext = static_cast<const FBlackbirdGameplayEffectContext*>(
		EffectContextHandle.Get()))
	{
		return AuraEffectContext->GetKnockbackVector();
	}
	return FVector::ZeroVector;
}

void UBlackbirdAbilitySystemLibrary::SetKnockbackVector(FGameplayEffectContextHandle& EffectContextHandle,
                                                        const FVector& InKnockbackVector)
{
	if (FBlackbirdGameplayEffectContext* AuraEffectContext = static_cast<FBlackbirdGameplayEffectContext*>(
		EffectContextHandle.Get()))
	{
		AuraEffectContext->SetKnockbackVector(InKnockbackVector);
	}
}


FGameplayEffectContextHandle UBlackbirdAbilitySystemLibrary::ApplyDamageEffect(
	const FBlackbirdDamageEffectParams& DamageEffectParams)
{
	const FBlackbirdAttributeTags& GameplayTags = FBlackbirdAttributeTags::Get();
	const AActor* SourceAvatarActor = DamageEffectParams.SourceAbilitySystemComponent->GetAvatarActor();
	FGameplayEffectContextHandle EffectContextHandle = DamageEffectParams.SourceAbilitySystemComponent->
	                                                                      MakeEffectContext();
	EffectContextHandle.AddSourceObject(SourceAvatarActor);
	const FGameplayEffectSpecHandle SpecHandle = DamageEffectParams.SourceAbilitySystemComponent->MakeOutgoingSpec(
		DamageEffectParams.DamageGameplayEffectClass,
		DamageEffectParams.AbilityLevel,
		EffectContextHandle
	);
	SetDeathImpulse(EffectContextHandle, DamageEffectParams.DeathImpulse);
	SetKnockbackVector(EffectContextHandle, DamageEffectParams.KnockbackForce);
	if (DamageEffectParams.bIsRadialDamage)
	{
		SetIsRadialDamage(EffectContextHandle, DamageEffectParams.bIsRadialDamage);
		SetRadialDamageOrigin(EffectContextHandle, DamageEffectParams.RadialDamageOrigin);
		SetRadialDamageInnerRadius(EffectContextHandle, DamageEffectParams.RadialDamageInnerRadius);
		SetRadialDamageOuterRadius(EffectContextHandle, DamageEffectParams.RadialDamageOuterRadius);
	}
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(
		SpecHandle,
		GameplayTags.Attributes_Meta_IncomingDamage,
		DamageEffectParams.BaseDamage
	);
	DamageEffectParams.TargetAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data);
	return EffectContextHandle;
}

FBlackbirdDamageEffectParams UBlackbirdAbilitySystemLibrary::MakeCustomDamageEffectParams(
	AActor* SourceActor,
	AActor* TargetActor,
	TSubclassOf<UGameplayEffect> DamageEffectClass,
	const FBlackbirdDamageConfig& InDamageConfig,
	int32 AbilityLevel,
	FVector RadialDamageOrigin,
	bool bOverrideKnockbackDirection,
	FVector InKnockbackDirectionOverride,
	bool bOverrideDeathImpulse,
	FVector InDeathImpulseDirectionOverride,
	bool bOverridePitch,
	float PitchOverride
)
{
	FBlackbirdDamageEffectParams DamageEffectParams;
	DamageEffectParams.RadialDamageOrigin = RadialDamageOrigin;
	DamageEffectParams.FillFromDamageConfig(InDamageConfig);
	DamageEffectParams.WorldContextObject = SourceActor;
	DamageEffectParams.DamageGameplayEffectClass = DamageEffectClass;
	DamageEffectParams.SourceAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(
		SourceActor
	);
	DamageEffectParams.TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(
		TargetActor
	);
	DamageEffectParams.AbilityLevel = AbilityLevel;
	DamageEffectParams.BaseDamage = InDamageConfig.GetDamageAtLevel(AbilityLevel);
	if (IsValid(TargetActor))
	{
		FRotator Rotation = (TargetActor->GetActorLocation() - SourceActor->GetActorLocation())
			.Rotation();
		if (bOverridePitch)
		{
			Rotation.Pitch = PitchOverride;
		}
		else if (IsValid(TargetActor))
		{
			Rotation.Pitch = 25.f;
		}
		if (!bOverrideKnockbackDirection)
		{
			if (DamageEffectParams.RollForKnockbackChance())
			{
				DamageEffectParams.KnockbackForce = Rotation.Vector() * DamageEffectParams.KnockbackForceMagnitude;
			}
		}
		if (!bOverrideDeathImpulse)
		{
			DamageEffectParams.DeathImpulse = Rotation.Vector() * DamageEffectParams.DeathImpulseMagnitude;
		}
	}
	if (bOverrideKnockbackDirection)
	{
		InKnockbackDirectionOverride.Normalize();
		DamageEffectParams.KnockbackForce = InKnockbackDirectionOverride * InDamageConfig.KnockbackForceMagnitude;
		if (bOverridePitch)
		{
			FRotator KnockbackRotation = InKnockbackDirectionOverride.Rotation();
			KnockbackRotation.Pitch = PitchOverride;
			DamageEffectParams.KnockbackForce = KnockbackRotation.Vector() * InDamageConfig.KnockbackForceMagnitude;
		}
	}
	if (bOverrideDeathImpulse)
	{
		InDeathImpulseDirectionOverride.Normalize();
		DamageEffectParams.DeathImpulse = InDeathImpulseDirectionOverride * InDamageConfig.DeathImpulseMagnitude;
		if (bOverridePitch)
		{
			FRotator DeathImpulseRotation = InDeathImpulseDirectionOverride.Rotation();
			DeathImpulseRotation.Pitch = PitchOverride;
			DamageEffectParams.DeathImpulse = DeathImpulseRotation.Vector() * InDamageConfig.DeathImpulseMagnitude;
		}
	}
	return DamageEffectParams;
}

bool UBlackbirdAbilitySystemLibrary::IsShielded(const UAbilitySystemComponent* Target)
{
	return Target->HasAllMatchingGameplayTags(
		FBlackbirdAbilitySystemTags::Get().Abilities_Effect_Shielded.GetSingleTagContainer());
}
