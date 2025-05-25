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
#include "AbilitySystem/BlackbirdAbilitySystemLibrary.h"
#include "Net/UnrealNetwork.h"


// Sets default values
ABlackbirdProjectileActor::ABlackbirdProjectileActor()
{
	PrimaryActorTick.bCanEverTick = false;
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
	const AActor* SourceAvatarActor = DamageEffectParams.SourceAbilitySystemComponent->GetAvatarActor();
	if (SourceAvatarActor == OtherActor)
	{
		return;
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
		}
		Destroy();
	}
}
