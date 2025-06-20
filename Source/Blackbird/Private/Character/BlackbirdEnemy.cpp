// Copyright Alien Shores 2025


#include "Character/BlackbirdEnemy.h"

#include "AbilitySystem/Attribute/BlackbirdAttributeSet.h"
#include "AbilitySystem/BlackbirdAbilitySystemComponent.h"
#include "Blackbird/Blackbird.h"
#include "Pickup/BlackbirdDropPickupComponent.h"
#include "Pickup/BlackbirdPickup.h"


// Sets default values
ABlackbirdEnemy::ABlackbirdEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	IgnoreInstigatorTags.Add(TAG_ENEMY);
	AbilitySystemComponent = CreateDefaultSubobject<UBlackbirdAbilitySystemComponent>(TEXT("Ability System Component"));
	AttributeSet = CreateDefaultSubobject<UBlackbirdAttributeSet>(TEXT("Attribute Set"));
	DropComponent = CreateDefaultSubobject<UBlackbirdDropPickupComponent>(TEXT("Drop Component"));
}

// Called when the game starts or when spawned
void ABlackbirdEnemy::BeginPlay()
{
	Super::BeginPlay();
	InitAbilitySystem(this, GetBlackbirdAbilitySystemComponent());
}

void ABlackbirdEnemy::OnReceivedDamage(const FOnReceivedDamagePayload& Payload)
{
	if (Payload.IsFatal())
	{
		for (TArray<ABlackbirdPickup*> Drops = DropComponent->Drop(); ABlackbirdPickup* Drop : Drops)
		{
			Drop->SetHomingActor(Payload.DamagedBy, 1.f);
			OnDrop(Drop);
		}
	}
	Super::OnReceivedDamage(Payload);
}

// Called every frame
void ABlackbirdEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
