// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BlackbirdPlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/BlackbirdAbilitySystemComponent.h"
#include "Blackbird/Blackbird.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Player/BlackbirdPlayerState.h"
#include "Player/PlayerTargetingComponent.h"


// Sets default values
ABlackbirdPlayerCharacter::ABlackbirdPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = true;
	SpringArm->bInheritRoll = false;
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;
	TargetingComponent = CreateDefaultSubobject<UPlayerTargetingComponent>(TEXT("Targeting Component"));
	IgnoreInstigatorTags.Add(TAG_PLAYER);
}

void ABlackbirdPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}


void ABlackbirdPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABlackbirdPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABlackbirdPlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	InitAbilityActorInfo();
}

void ABlackbirdPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitAbilityActorInfo();
}

UBlackbirdAbilitySystemComponent* ABlackbirdPlayerCharacter::GetBlackbirdAbilitySystemComponent() const
{
	return Cast<UBlackbirdAbilitySystemComponent>(AbilitySystemComponent);
}

ABlackbirdPlayerState* ABlackbirdPlayerCharacter::GetBlackbirdPlayerState() const
{
	return Cast<ABlackbirdPlayerState>(GetPlayerState());
}

UPlayerTargetingComponent* ABlackbirdPlayerCharacter::GetTargetingComponent() const
{
	return TargetingComponent;
}

void ABlackbirdPlayerCharacter::InitAbilityActorInfo()
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
