// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "GameplayPrediction.h"
#include "Ability/BlackbirdProjectileActor.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BlackbirdAbilitySystemLibrary.generated.h"

class UGameplayEffect;
struct FGameplayEffectModCallbackData;
struct FGameplayEffectContextHandle;
struct FGameplayAbilitySpec;
/**
 * 
 */
UCLASS()
class BLACKBIRD_API UBlackbirdAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static void ApplyEffectToSelf(AActor* Actor, const TSubclassOf<UGameplayEffect>& Effect, int32 Level = 1);
	static FPredictionKey GetPredictionKeyFromAbilitySpec(const FGameplayAbilitySpec& AbilitySpec);

	/** Attribute Manipulation **/
	static FGameplayEffectContextHandle GetEffectContextHandle(const FGameplayEffectModCallbackData& Data);
	static UAbilitySystemComponent* GetEffectSourceAbilitySystemComponent(const FGameplayEffectModCallbackData& Data);
	static AActor* GetEffectSourceAvatarActor(const FGameplayEffectModCallbackData& Data);
	static ACharacter* GetEffectSourceCharacter(const FGameplayEffectModCallbackData& Data);
	static AController* GetEffectSourceController(const FGameplayEffectModCallbackData& Data);
	static AActor* GetEffectTargetAvatarActor(const FGameplayEffectModCallbackData& Data);
	static AController* GetEffectTargetController(const FGameplayEffectModCallbackData& Data);
	static ACharacter* GetEffectTargetCharacter(const FGameplayEffectModCallbackData& Data);
	static UAbilitySystemComponent* GetEffectTargetAbilitySystemComponent(const FGameplayEffectModCallbackData& Data);

	static bool IsAlive(AActor* Actor);
	static bool IsDead(AActor* Actor);

	/** Gameplay Effect Context */
	UFUNCTION(BlueprintPure, Category="BlackbirdAbilitySystemLibrary|GameplayEffect")
	static bool IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle);
	UFUNCTION(BlueprintCallable, Category="BlackbirdAbilitySystemLibrary|GameplayEffect")
	static void SetIsBlockedHit(
		UPARAM(ref)
		FGameplayEffectContextHandle& Context,
		bool InIsBlocked
	);
	UFUNCTION(BlueprintPure, Category="BlackbirdAbilitySystemLibrary|GameplayEffect")
	static bool IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle);
	UFUNCTION(BlueprintCallable, Category="BlackbirdAbilitySystemLibrary|GameplayEffect")
	static void SetIsCriticalHit(
		UPARAM(ref)
		FGameplayEffectContextHandle& Context,
		bool InIsCriticalHit
	);
	UFUNCTION(BlueprintPure, Category="BlackbirdAbilitySystemLibrary|GameplayEffect")
	static bool IsRadialDamage(const FGameplayEffectContextHandle& EffectContextHandle);
	UFUNCTION(BlueprintPure, Category="BlackbirdAbilitySystemLibrary|GameplayEffect")
	static float GetRadialDamageInnerRadius(const FGameplayEffectContextHandle& EffectContextHandle);
	UFUNCTION(BlueprintPure, Category="BlackbirdAbilitySystemLibrary|GameplayEffect")
	static float GetRadialDamageOuterRadius(const FGameplayEffectContextHandle& EffectContextHandle);
	UFUNCTION(BlueprintPure, Category="BlackbirdAbilitySystemLibrary|GameplayEffect")
	static FVector GetRadialDamageOrigin(const FGameplayEffectContextHandle& EffectContextHandle);
	UFUNCTION(BlueprintCallable, Category="BlackbirdAbilitySystemLibrary|GameplayEffect")
	static void SetIsRadialDamage(FGameplayEffectContextHandle& EffectContextHandle, bool InIsRadialDamage);
	UFUNCTION(BlueprintCallable, Category="BlackbirdAbilitySystemLibrary|GameplayEffect")
	static void SetRadialDamageInnerRadius(
		FGameplayEffectContextHandle& EffectContextHandle,
		float InRadialDamageInnerRadius
	);
	UFUNCTION(BlueprintCallable, Category="BlackbirdAbilitySystemLibrary|GameplayEffect")
	static void SetRadialDamageOuterRadius(
		FGameplayEffectContextHandle& EffectContextHandle,
		float InRadialDamageOuterRadius
	);
	UFUNCTION(BlueprintCallable, Category="BlackbirdAbilitySystemLibrary|GameplayEffect")
	static void SetRadialDamageOrigin(
		FGameplayEffectContextHandle& EffectContextHandle,
		const FVector& InRadialDamageOrigin
	);
	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|GameplayEffect")
	static FVector GetDeathImpulse(const FGameplayEffectContextHandle& EffectContextHandle);
	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|GameplayEffect")
	static void SetDeathImpulse(
		UPARAM(ref)
		FGameplayEffectContextHandle& EffectContextHandle,
		const FVector& InDeathImpulse
	);
	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|GameplayEffect")
	static FVector GetKnockbackVector(const FGameplayEffectContextHandle& EffectContextHandle);
	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|GameplayEffect")
	static void SetKnockbackVector(
		UPARAM(ref)
		FGameplayEffectContextHandle& EffectContextHandle,
		const FVector& InKnockbackVector
	);


	UFUNCTION(BlueprintCallable, Category="BlackbirdAbilitySystemLibrary|GameplayEffect")
	static FGameplayEffectContextHandle ApplyDamageEffect(const FBlackbirdDamageEffectParams& DamageEffectParams);


	static FBlackbirdDamageEffectParams MakeCustomDamageEffectParams(
		AActor* SourceActor,
		AActor* TargetActor,
		TSubclassOf<UGameplayEffect> DamageEffectClass,
		const FBlackbirdDamageConfig& InDamageConfig,
		int32 AbilityLevel,
		FVector RadialDamageOrigin = FVector::ZeroVector,
		bool bOverrideKnockbackDirection = false,
		FVector InKnockbackDirectionOverride = FVector::ZeroVector,
		bool bOverrideDeathImpulse = false,
		FVector InDeathImpulseDirectionOverride = FVector::ZeroVector,
		bool bOverridePitch = false,
		float PitchOverride = 0.f
	);
};
