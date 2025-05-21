// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "GameplayPrediction.h"
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
};
