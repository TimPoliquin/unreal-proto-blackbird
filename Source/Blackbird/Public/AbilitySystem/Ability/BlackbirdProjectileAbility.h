// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "BlackbirdDamageGameplayAbility.h"
#include "BlackbirdProjectileActor.h"
#include "BlackbirdProjectileAbility.generated.h"

DECLARE_DELEGATE_OneParam(FOnSpawnProjectileFinishedSignature, ABlackbirdProjectileActor*);

class ABlackbirdProjectileActor;
/**
 * 
 */
UCLASS()
class BLACKBIRD_API UBlackbirdProjectileAbility : public UBlackbirdDamageGameplayAbility
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable, Category ="Projectile")
	ABlackbirdProjectileActor* SpawnProjectile(
		const FGameplayTag& SocketTag,
		const FVector& ImpactPoint,
		const AActor* HitActor,
		bool bInheritOwnerVelocity = true
	);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	TSubclassOf<ABlackbirdProjectileActor> ProjectileClass;

private:
	FGameplayEffectSpecHandle MakeDamageEffectSpecHandle(AActor* SourceObject, const FVector& TargetLocation) const;
	FVector GetProjectileSpawnLocation(const FGameplayTag& SocketTag) const;
	FRotator GetProjectileSpawnRotation(const FVector& SpawnLocation, const FVector& ImpactPoint) const;

	ABlackbirdProjectileActor* SpawnProjectile(
		const FVector& SpawnLocation,
		const FRotator& SpawnRotation,
		const AActor* HitActor,
		bool bInheritOwnerVelocity,
		const FOnSpawnProjectileFinishedSignature* BeforeFinishSpawning = nullptr
	) const;
};
