// Copyright Alien Shores 2025


#include "AbilitySystem/Ability/BlackbirdDestructibleProjectileActor.h"

#include "AbilitySystem/BlackbirdAbilitySystemLibrary.h"
#include "AbilitySystem/Attribute/BlackbirdBasicAttributeSet.h"


// Sets default values
ABlackbirdDestructibleProjectileActor::ABlackbirdDestructibleProjectileActor()
{
	PrimaryActorTick.bCanEverTick = true;
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
	AttributeSet = CreateDefaultSubobject<UBlackbirdBasicAttributeSet>(TEXT("Attribute Set"));
}

UAbilitySystemComponent* ABlackbirdDestructibleProjectileActor::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

bool ABlackbirdDestructibleProjectileActor::CanBeDamagedByInstigatorTag(const FName& InstigatorTag) const
{
	if (const IDamageableInterface* DamageableInstigator = Cast<IDamageableInterface>(GetInstigator()))
	{
		return DamageableInstigator->CanBeDamagedByInstigatorTag(InstigatorTag);
	}
	return false;
}

FOnDamageSignature& ABlackbirdDestructibleProjectileActor::GetOnDamageDelegate()
{
	return OnDamageDelegate;
}

bool ABlackbirdDestructibleProjectileActor::IsAlive() const
{
	return AttributeSet->IsAlive();
}

bool ABlackbirdDestructibleProjectileActor::IsDead() const
{
	return AttributeSet->IsDead();
}

// Called when the game starts or when spawned
void ABlackbirdDestructibleProjectileActor::BeginPlay()
{
	Super::BeginPlay();
	InitializeAbilitySystem();
	AttributeSet->OnReceivedDamage.AddDynamic(this, &ABlackbirdDestructibleProjectileActor::OnReceivedDamage);
}

void ABlackbirdDestructibleProjectileActor::InitializeAbilitySystem()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	UBlackbirdAbilitySystemLibrary::ApplyEffectToSelf(this, SetupInitialAttributes);
}

void ABlackbirdDestructibleProjectileActor::OnReceivedDamage(const FOnReceivedDamagePayload& Payload)
{
	if (Payload.bFatal)
	{
		Explode();
		Destroy();
	}
	else
	{
		OnDamageDelegate.Broadcast(Payload.DamageAmount);
	}
}
