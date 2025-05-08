// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BlackbirdPlayerShip.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
ABlackbirdPlayerShip::ABlackbirdPlayerShip()
{
	PrimaryActorTick.bCanEverTick = true;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation =false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;
}

void ABlackbirdPlayerShip::BeginPlay()
{
	Super::BeginPlay();
}

void ABlackbirdPlayerShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABlackbirdPlayerShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
