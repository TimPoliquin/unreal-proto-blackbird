// Copyright Alien Shores 2025


#include "AbilitySystem/Ability/BlackbirdProjectileActor.h"

#include "Blackbird/Blackbird.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
ABlackbirdProjectileActor::ABlackbirdProjectileActor()
{
	PrimaryActorTick.bCanEverTick = false;
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

// Called when the game starts or when spawned
void ABlackbirdProjectileActor::BeginPlay()
{
	Super::BeginPlay();
}


