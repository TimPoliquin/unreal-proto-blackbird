// Copyright Alien Shores 2025


#include "Ship/BlackbirdEnemyShip.h"

#include "AbilitySystem/BlackbirdAbilitySystemComponent.h"


// Sets default values
ABlackbirdEnemyShip::ABlackbirdEnemyShip()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AbilitySystemComponent = CreateDefaultSubobject<UBlackbirdAbilitySystemComponent>(TEXT("Ability System Component"));
}

// Called when the game starts or when spawned
void ABlackbirdEnemyShip::BeginPlay()
{
	Super::BeginPlay();
	InitAbilitySystem(this, GetBlackbirdAbilitySystemComponent());
}

// Called every frame
void ABlackbirdEnemyShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

