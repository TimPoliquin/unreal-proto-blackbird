// Fill out your copyright notice in the Description page of Project Settings.


#include "Ship/BlackbirdShip.h"

#include "AbilitySystem/BlackbirdAbilitySystemComponent.h"
#include "AbilitySystem/Ability/BlackbirdAbilityAssignment.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


ABlackbirdShip::ABlackbirdShip()
{
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	Cast<UCharacterMovementComponent>(GetMovementComponent())->GravityScale = 0.f;
}

void ABlackbirdShip::BeginPlay()
{
	Super::BeginPlay();
}

void ABlackbirdShip::InitAbilitySystem(
	AActor* OwnerActor,
	UBlackbirdAbilitySystemComponent* InAbilitySystemComponent
)
{
	AbilitySystemComponent = Cast<UAbilitySystemComponent>(InAbilitySystemComponent);
	AbilitySystemComponent->InitAbilityActorInfo(OwnerActor, this);
	OnAbilitySystemReady(InAbilitySystemComponent);
	OnAbilitySystemReadyDelegate.Broadcast(InAbilitySystemComponent);
}

void ABlackbirdShip::InitDefaultAbilities()
{
	if (StartingAbilities == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Starting Abilities is null"));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Adding Starting Abilities"));
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

void ABlackbirdShip::SetFacingDirection(const FVector& Direction)
{
}


