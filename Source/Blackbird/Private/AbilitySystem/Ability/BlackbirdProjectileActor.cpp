// Copyright Alien Shores 2025


#include "AbilitySystem/Ability/BlackbirdProjectileActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Blackbird/Blackbird.h"
#include "Components/AudioComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "AbilitySystem/BlackbirdAbilitySystemComponent.h"
#include "AbilitySystem/BlackbirdAbilitySystemLibrary.h"
#include "AbilitySystem/Damage/DamageableInterface.h"
#include "Net/UnrealNetwork.h"
#include "Targeting/TargetingUtils.h"


// Sets default values
ABlackbirdProjectileActor::ABlackbirdProjectileActor()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	CapsuleComponent->SetCollisionObjectType(ECC_Projectile);
	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CapsuleComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	CapsuleComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	CapsuleComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	CapsuleComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	CapsuleComponent->IgnoreActorWhenMoving(GetOwner(), true);
	SetRootComponent(CapsuleComponent);
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	StaticMeshComponent->SetupAttachment(GetRootComponent());
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	StaticMeshComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Component"));
}

void ABlackbirdProjectileActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABlackbirdProjectileActor, DamageEffectParams);
}

void ABlackbirdProjectileActor::SetDamageEffectParams(FBlackbirdDamageEffectParams& Params)
{
	DamageEffectParams = Params;
}

UProjectileMovementComponent* ABlackbirdProjectileActor::GetProjectileMovementComponent_Implementation() const
{
	return ProjectileComponent;
}

void ABlackbirdProjectileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (ProjectileComponent && ProjectileComponent->bIsHomingProjectile)
	{
		Lifetime += DeltaTime;
		if (!FMath::IsNearlyZero(HomingLifetime) && Lifetime > HomingLifetime)
		{
			ProjectileComponent->bIsHomingProjectile = false;
			SetActorTickEnabled(false);
		}
	}
}

void ABlackbirdProjectileActor::Repel_Implementation(AActor* NewOwner, const FHitResult& NewTarget, const float RepelAngle, const float BaseDamageMultiplier)
{
	SetOwner(NewOwner);
	SetInstigator(Cast<APawn>(NewOwner));
	DamageEffectParams.SourceAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(NewOwner);
	DamageEffectParams.BaseDamage *= BaseDamageMultiplier;
	const FVector OwnerToProjectile = NewOwner->GetActorLocation() - GetActorLocation();
	const FVector OwnerToTarget = NewOwner->GetActorLocation() - NewTarget.ImpactPoint;
	const float AngleToProjectile = UTargetingUtils::CalculateAngleBetweenVectors(OwnerToProjectile, OwnerToTarget); 
	if (AngleToProjectile <= RepelAngle)
	{
		// projectile should be repelled toward the cursor target
		UE_LOG(LogTemp, Display, TEXT("[%s] Projectile repelled to target. [%f] <= [%f]"), *GetName(), AngleToProjectile, RepelAngle);
		ProjectileComponent->bIsHomingProjectile = NewTarget.bBlockingHit;
		ProjectileComponent->HomingTargetComponent = NewTarget.bBlockingHit ? NewTarget.GetActor()->GetRootComponent() : nullptr;
		ProjectileComponent->HomingAccelerationMagnitude = NewTarget.bBlockingHit ? 1000.f : 0.f;
		ProjectileComponent->Velocity = ((NewTarget.ImpactPoint - GetActorLocation()).GetSafeNormal()) * ProjectileComponent->MaxSpeed + NewOwner->GetVelocity();
	} else
	{
		// projectile direction should be reversed
		UE_LOG(LogTemp, Display, TEXT("[%s] Projectile reversed. [%f] > [%f]"), *GetName(), AngleToProjectile, RepelAngle);
		ProjectileComponent->bIsHomingProjectile = false;
		ProjectileComponent->HomingTargetComponent = nullptr;
		ProjectileComponent->HomingAccelerationMagnitude = 0.f;
		ProjectileComponent->Velocity = OwnerToProjectile.GetSafeNormal() * -1 * ProjectileComponent->MaxSpeed + NewOwner->GetVelocity();
	}
	SetLifeSpan(5.f);
}

// Called when the game starts or when spawned
void ABlackbirdProjectileActor::BeginPlay()
{
	Super::BeginPlay();
	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &ABlackbirdProjectileActor::OnCollisionBeginOverlap);
	SetReplicateMovement(true);
	SetLifeSpan(MaxLifetime);
	PlayTravelSound();
}

void ABlackbirdProjectileActor::Destroyed()
{
	if (!HasAuthority())
	{
		PlayImpactEffect();
	}
	Super::Destroyed();
}

FVector ABlackbirdProjectileActor::GetImpactDirection(const AActor* HitActor) const
{
	if (IsValid(HitActor))
	{
		return HitActor->GetActorLocation() - GetActorLocation();
	}
	return FVector::ZeroVector;
}

void ABlackbirdProjectileActor::PlayTravelSound()
{
	if (TravelSound)
	{
		TravelSoundComponent = UGameplayStatics::SpawnSoundAttached(TravelSound, GetRootComponent());
	}
	if (TravelSoundComponent)
	{
		TravelSoundComponent->SetSound(TravelSound);
		TravelSoundComponent->Play();
	}
}

void ABlackbirdProjectileActor::PlayImpactEffect()
{
	if (bHit)
	{
		// Only play the impact effect once
		return;
	}
	if (ImpactSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(), FRotator::ZeroRotator);
	}
	if (ImpactEffect)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect, GetActorLocation());
	}
	if (TravelSoundComponent)
	{
		TravelSoundComponent->Stop();
		TravelSoundComponent->DestroyComponent();
	}
	bHit = true;
}

void ABlackbirdProjectileActor::OnCollisionBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool BFromSweep,
	const FHitResult& SweepResult
)
{
	if (!HasAuthority())
	{
		return;
	}
	const AActor* SourceAvatarActor = DamageEffectParams.SourceAbilitySystemComponent->GetAvatarActor();
	// don't damage yourself with your own projectiles, dummy!
	if (!IsValid(SourceAvatarActor) || !IsValid(OtherActor) || SourceAvatarActor == OtherActor)
	{
		return;
	}
	// don't damage your friends with your projectiles, dummy!
	if (const IDamageableInterface* DamageableInterface = Cast<IDamageableInterface>(OtherActor))
	{
		for (const FName& InstigatorTag : SourceAvatarActor->Tags)
		{
			if (!DamageableInterface->CanBeDamagedByInstigatorTag(InstigatorTag))
			{
				return;
			}
		}
	}
	PlayImpactEffect();
	if (HasAuthority())
	{
		if (UAbilitySystemComponent* OtherAbilitySystem = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(
			OtherActor
		))
		{
			DamageEffectParams.DeathImpulse = GetActorForwardVector() * DamageEffectParams.DeathImpulseMagnitude;
			if (FMath::RandRange(1, 100) < DamageEffectParams.KnockbackChance)
			{
				FRotator Rotation = GetActorRotation();
				Rotation.Pitch = 45.f;
				DamageEffectParams.KnockbackForce = Rotation.Vector() * DamageEffectParams.KnockbackForceMagnitude;
			}
			DamageEffectParams.TargetAbilitySystemComponent = OtherAbilitySystem;
			UBlackbirdAbilitySystemLibrary::ApplyDamageEffect(DamageEffectParams);
			UE_LOG(LogTemp, Warning, TEXT("[%s] Destroyed on collision with %s (AS)"), *GetName(), *OtherActor->GetName())
			Destroy();
		}
		else if (!Implements<UDamageableInterface>())
		{
			UE_LOG(LogTemp, Warning, TEXT("[%s] Destroyed on collision with %s (!Damageable)"), *GetName(), *OtherActor->GetName())
			Destroy();
		}
	}
}
