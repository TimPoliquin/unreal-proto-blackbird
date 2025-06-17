// Copyright Alien Shores 2025


#include "AbilitySystem/Ability/BlackbirdProjectileAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/BlackbirdAbilitySystemLibrary.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Ship/SocketInterface.h"
#include "Targeting/TargetableInterface.h"
#include "Targeting/TargetingActorInterface.h"

ABlackbirdProjectileActor* UBlackbirdProjectileAbility::SpawnProjectile(
	const FGameplayTag& SocketTag,
	const FVector& ImpactPoint,
	const AActor* HitActor,
	bool bInheritOwnerVelocity
)
{
	AActor* OwningActor = GetAvatarActorFromActorInfo();
	if (!OwningActor->HasAuthority())
	{
		// Do not execute on client - run on server only
		return nullptr;
	}
	check(ProjectileClass);
	const FVector SpawnLocation = GetProjectileSpawnLocation(SocketTag);
	const FRotator Rotation = GetProjectileSpawnRotation(SpawnLocation, ImpactPoint);
	return SpawnProjectile(SpawnLocation, Rotation, HitActor, bInheritOwnerVelocity);
}


FVector UBlackbirdProjectileAbility::GetProjectileSpawnLocation(const FGameplayTag& SocketTag) const
{
	if (const ISocketInterface* SocketInterface = Cast<ISocketInterface>(GetAvatarActorFromActorInfo()))
	{
		return SocketInterface->GetSocketLocation(SocketTag);
	}
	return GetAvatarActorFromActorInfo()->GetActorLocation();
}

FRotator UBlackbirdProjectileAbility::GetProjectileSpawnRotation(const FVector& SpawnLocation, const FVector& ImpactPoint) const
{
	return UKismetMathLibrary::FindLookAtRotation(SpawnLocation, ImpactPoint);
}

ABlackbirdProjectileActor* UBlackbirdProjectileAbility::SpawnProjectile(
	const FVector& SpawnLocation,
	const FRotator& SpawnRotation,
	const AActor* HitActor,
	bool bInheritOwnerVelocity,
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
	UProjectileMovementComponent* ProjectileMovementComponent = IProjectileInterface::GetProjectileMovementComponent(SpawnedProjectile);
	if (ProjectileMovementComponent && ProjectileMovementComponent->bIsHomingProjectile && ITargetableInterface::IsTargetable(HitActor))
	{
		ProjectileMovementComponent->HomingTargetComponent = HitActor->GetRootComponent();
	}
	FBlackbirdDamageEffectParams DamageEffectParams = MakeDamageEffectParamsFromClassDefaults();
	SpawnedProjectile->SetDamageEffectParams(DamageEffectParams);
	if (BeforeFinishSpawning)
	{
		BeforeFinishSpawning->ExecuteIfBound(SpawnedProjectile);
	}
	SpawnedProjectile->FinishSpawning(SpawnTransform);
	// Spawned projectile's velocity is incorrect until after spawning is completed.
	if (bInheritOwnerVelocity && ProjectileMovementComponent)
	{
		ProjectileMovementComponent->Velocity += GetAvatarActorFromActorInfo()->GetVelocity();
	}
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
