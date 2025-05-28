// Copyright Alien Shores 2025


#include "AbilitySystem/Ability/BlackbirdProjectileAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/BlackbirdAbilitySystemLibrary.h"
#include "Ship/SocketInterface.h"

void UBlackbirdProjectileAbility::SpawnProjectile(const FGameplayTag& SocketTag, const FVector& ImpactPoint, const AActor* HitActor)
{
	AActor* OwningActor = GetAvatarActorFromActorInfo();
	if (!OwningActor->HasAuthority())
	{
		// Do not execute on client - run on server only
		return;
	}
	check(ProjectileClass);
	const FVector SpawnLocation = GetProjectileSpawnLocation(SocketTag);
	const FRotator Rotation = GetProjectileSpawnRotation(SpawnLocation, ImpactPoint, HitActor);
	SpawnProjectile(SpawnLocation, Rotation);
}


FVector UBlackbirdProjectileAbility::GetProjectileSpawnLocation(const FGameplayTag& SocketTag) const
{
	if (const ISocketInterface* SocketInterface = Cast<ISocketInterface>(GetAvatarActorFromActorInfo()))
	{
		return SocketInterface->GetSocketLocation(SocketTag);
	}
	return GetAvatarActorFromActorInfo()->GetActorLocation();
}

FRotator UBlackbirdProjectileAbility::GetProjectileSpawnRotation(const FVector& SpawnLocation, const FVector& ImpactPoint, const AActor* HitActor) const
{
	if (IsValid(HitActor))
	{
		return (ImpactPoint - SpawnLocation).Rotation();
	}
	// TODO - this isn't quite right - we probably want to project to some fake impact point in the distance based on the cursor position.
	return GetAvatarActorFromActorInfo()->GetActorForwardVector().Rotation();
}

ABlackbirdProjectileActor* UBlackbirdProjectileAbility::SpawnProjectile(
	const FVector& SpawnLocation,
	const FRotator& SpawnRotation,
	const FOnSpawnProjectileFinishedSignature* BeforeFinishSpawning
) const
{
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SpawnLocation);
	SpawnTransform.SetRotation(SpawnRotation.Quaternion());

	ABlackbirdProjectileActor* SpawnedProjectile = GetWorld()->SpawnActorDeferred<ABlackbirdProjectileActor>(
		ProjectileClass,
		SpawnTransform,
		GetAvatarActorFromActorInfo(),
		Cast<APawn>(GetAvatarActorFromActorInfo()),
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn
	);
	FBlackbirdDamageEffectParams DamageEffectParams = MakeDamageEffectParamsFromClassDefaults();
	SpawnedProjectile->SetDamageEffectParams(DamageEffectParams);
	if (BeforeFinishSpawning)
	{
		BeforeFinishSpawning->ExecuteIfBound(SpawnedProjectile);
	}
	SpawnedProjectile->FinishSpawning(SpawnTransform);
	return SpawnedProjectile;
}

FGameplayEffectSpecHandle UBlackbirdProjectileAbility::MakeDamageEffectSpecHandle(AActor* SourceObject, const FVector& TargetLocation) const
{
	const UAbilitySystemComponent* SourceAbilitySystem = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(
		GetAvatarActorFromActorInfo()
	);
	FGameplayEffectContextHandle ContextHandle = SourceAbilitySystem->MakeEffectContext();
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(SourceObject);
	// Add actors to the context
	TArray<TWeakObjectPtr<AActor>> Actors;
	Actors.Add(SourceObject);
	ContextHandle.AddActors(Actors);
	// Set hit result on the context
	FHitResult HitResult;
	HitResult.Location = TargetLocation;
	ContextHandle.AddHitResult(HitResult);
	// Create outgoing spec
	return SourceAbilitySystem->MakeOutgoingSpec(
		DamageEffectClass,
		GetAbilityLevel(),
		ContextHandle
	);
}
