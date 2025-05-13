// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BlackbirdPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/BlackbirdAbilitySystemComponent.h"
#include "Player/BlackbirdPlayerState.h"
#include "Ship/ShipInterface.h"


ABlackbirdPlayerController::ABlackbirdPlayerController()
{
	bReplicates = true;
}

void ABlackbirdPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(InputContext);
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer()
	))
	{
		Subsystem->AddMappingContext(InputContext, 0);
	}
}

void ABlackbirdPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABlackbirdPlayerController::Move);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &ABlackbirdPlayerController::EndMove);
		BindAbilityActions(
			InputConfig,
			EnhancedInputComponent,
			this,
			&ABlackbirdPlayerController::AbilityInputTagPressed,
			&ABlackbirdPlayerController::AbilityInputTagReleased,
			&ABlackbirdPlayerController::AbilityInputTagHeld
		);
	}
}

void ABlackbirdPlayerController::Move(const FInputActionValue& Value)
{
	const FVector2D InputAxisVector = Value.Get<FVector2D>();
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(FVector::ForwardVector, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(FVector::RightVector, InputAxisVector.X);
	}
	if (IShipInterface* ShipInterface = GetPawn<IShipInterface>())
	{
		ShipInterface->SetRollAmount(InputAxisVector.X);
	}
}

void ABlackbirdPlayerController::EndMove(const FInputActionValue& InputActionValue)
{
	if (IShipInterface* ShipInterface = GetPawn<IShipInterface>())
	{
		ShipInterface->SetRollAmount(0.f);
	}
}

void ABlackbirdPlayerController::AbilityInputTagPressed(const FGameplayTag InputTag)
{
	if (UBlackbirdAbilitySystemComponent* BlackbirdAbilitySystemComponent = GetPlayerState<ABlackbirdPlayerState>()->GetBlackbirdAbilitySystemComponent())
	{
		BlackbirdAbilitySystemComponent->AbilityInputTagPressed(InputTag);
	}
}

void ABlackbirdPlayerController::AbilityInputTagReleased(const FGameplayTag InputTag)
{
	if (UBlackbirdAbilitySystemComponent* BlackbirdAbilitySystemComponent = GetPlayerState<ABlackbirdPlayerState>()->GetBlackbirdAbilitySystemComponent())
	{
		BlackbirdAbilitySystemComponent->AbilityInputTagHeld(InputTag);
	}
}

void ABlackbirdPlayerController::AbilityInputTagHeld(const FGameplayTag InputTag)
{
	if (UBlackbirdAbilitySystemComponent* LocalAbilitySystemComponent = GetPlayerState<ABlackbirdPlayerState>()->GetBlackbirdAbilitySystemComponent())
	{
		LocalAbilitySystemComponent->AbilityInputTagReleased(InputTag);
	}
}
