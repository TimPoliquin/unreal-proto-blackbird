// Fill out your copyright notice in the Description page of Project Settings.


#include "Ship/BlackbirdShip.h"

#include "AbilitySystem/BlackbirdAbilitySystemComponent.h"
#include "AbilitySystem/Ability/BlackbirdAbilityAssignment.h"
#include "Components/BoxComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Ship/BlackbirdShipMovementComponent.h"


ABlackbirdShip::ABlackbirdShip()
{
	PrimaryActorTick.bCanEverTick = true;
	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Component"));
	SetRootComponent(Collision);
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	Mesh->SetupAttachment(GetRootComponent());
	ShipMovementComponent = CreateDefaultSubobject<UBlackbirdShipMovementComponent>(TEXT("Ship Movement"));
	ShipMovementComponent->UpdatedComponent = GetRootComponent();
}

void ABlackbirdShip::BeginPlay()
{
	Super::BeginPlay();
	OnAbilitySystemReadyDelegate.AddDynamic(this, &ABlackbirdShip::OnAbilitySystemReady);
}

void ABlackbirdShip::InitAbilitySystem(
	AActor* OwnerActor,
	UBlackbirdAbilitySystemComponent* InAbilitySystemComponent
)
{
	AbilitySystemComponent = Cast<UAbilitySystemComponent>(InAbilitySystemComponent);
	AbilitySystemComponent->InitAbilityActorInfo(OwnerActor, this);
	OnAbilitySystemReadyDelegate.Broadcast(InAbilitySystemComponent);
}

void ABlackbirdShip::InitDefaultAbilities()
{
	if (StartingAbilities == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Starting Abilities is null"));
		return;
	} 
	GetBlackbirdAbilitySystemComponent()->AddAbilities(StartingAbilities->GetAbilityAssignments());
}

void ABlackbirdShip::OnAbilitySystemReady(UBlackbirdAbilitySystemComponent* BlackbirdAbilitySystemComponent)
{
	InitDefaultAbilities();
}

void ABlackbirdShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABlackbirdShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

UAbilitySystemComponent* ABlackbirdShip::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UBlackbirdAbilitySystemComponent* ABlackbirdShip::GetBlackbirdAbilitySystemComponent()
{
	return Cast<UBlackbirdAbilitySystemComponent>(AbilitySystemComponent);
}

void ABlackbirdShip::SetRollAmount(const float InRollDirection)
{
	ShipMovementComponent->SetRollAmount(InRollDirection);
}

void ABlackbirdShip::SetFacingDirection(const FVector& Direction)
{
}


