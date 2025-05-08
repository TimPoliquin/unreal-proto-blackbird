// Fill out your copyright notice in the Description page of Project Settings.


#include "Ship/BlackbirdShip.h"

#include "Components/BoxComponent.h"
#include "GameFramework/FloatingPawnMovement.h"


ABlackbirdShip::ABlackbirdShip()
{
	PrimaryActorTick.bCanEverTick = true;
	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Component"));
	SetRootComponent(Collision);
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	Mesh->SetupAttachment(GetRootComponent());
	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Floating Pawn Movement"));
	FloatingPawnMovement->UpdatedComponent = GetRootComponent();
}

void ABlackbirdShip::BeginPlay()
{
	Super::BeginPlay();
}

void ABlackbirdShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!FMath::IsNearlyEqual(GetActorRotation().Roll, IntendedRollAmount, 0.01f))
	{
		CurrentRollTime += DeltaTime;
		SetActorRotation(FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw, FMath::Lerp(InitialRollAmount, IntendedRollAmount, CurrentRollTime/RollTime)));
	}
}

void ABlackbirdShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABlackbirdShip::SetRollAmount(const float InRollDirection)
{
	if (!FMath::IsNearlyEqual(InRollDirection * RollAmount, IntendedRollAmount, 0.01f))
	{
		InitialRollAmount = GetActorRotation().Roll;
		IntendedRollAmount = InRollDirection * RollAmount;
		CurrentRollTime = 0.f;
	}
}

void ABlackbirdShip::SetFacingDirection(const FVector& Direction)
{
}


