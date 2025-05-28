// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BlackbirdPlayerShip.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/BlackbirdAbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/BlackbirdPlayerState.h"
#include "Player/PlayerTargetingComponent.h"


// Sets default values
ABlackbirdPlayerShip::ABlackbirdPlayerShip()
{
	PrimaryActorTick.bCanEverTick = true;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = true;
	SpringArm->bInheritRoll = false;
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;
	TargetingComponent = CreateDefaultSubobject<UPlayerTargetingComponent>(TEXT("Targeting Component"));
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

void ABlackbirdPlayerShip::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	InitAbilityActorInfo();
}

void ABlackbirdPlayerShip::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitAbilityActorInfo();
}

UBlackbirdAbilitySystemComponent* ABlackbirdPlayerShip::GetBlackbirdAbilitySystemComponent() const
{
	return Cast<UBlackbirdAbilitySystemComponent>(AbilitySystemComponent);
}

ABlackbirdPlayerState* ABlackbirdPlayerShip::GetBlackbirdPlayerState() const
{
	return Cast<ABlackbirdPlayerState>(GetPlayerState());
}

UPlayerTargetingComponent* ABlackbirdPlayerShip::GetTargetingComponent() const
{
	return TargetingComponent;
}

void ABlackbirdPlayerShip::InitAbilityActorInfo()
{
	if (ABlackbirdPlayerState* BlackbirdPlayerState = Cast<ABlackbirdPlayerState>(GetPlayerState()))
	{
		AttributeSet = BlackbirdPlayerState->GetBlackbirdAttributeSet();
		InitAbilitySystem(BlackbirdPlayerState, BlackbirdPlayerState->GetBlackbirdAbilitySystemComponent());
		UE_LOG(
			LogTemp,
			Warning,
			TEXT("[%s %s] BlackbirdAbilitySystemInitialized"),
			*(HasAuthority() ? FString("Server") : FString("Client")),
			*GetName()
		);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("BlackbirdPlayerState is null"));
	}
}
