// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BlackbirdPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/BlackbirdAbilitySystemComponent.h"
#include "Track/BlackbirdCart.h"
#include "Track/BlackbirdTrack.h"
#include "Player/BlackbirdPlayerState.h"
#include "Player/PlayerTargetingComponent.h"
#include "Ship/MoveTarget.h"
#include "Targeting/TargetingActorInterface.h"


ABlackbirdPlayerController::ABlackbirdPlayerController()
{
	bReplicates = true;
}

void ABlackbirdPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (MoveTarget.IsActive())
	{
		MoveTarget.IncrementTime(DeltaSeconds);
		GetPawn()->SetActorRelativeLocation(MoveTarget.GetLocation());
		GetPawn()->SetActorRelativeRotation(MoveTarget.GetRotation());
	}
	if (PlayerTargetingComponent)
	{
		PlayerTargetingComponent->CursorTrace(this);
	}
}

void ABlackbirdPlayerController::BeginPlay()
{
	Super::BeginPlay();
	InitializeCursor();
	check(InputContext);
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer()
	))
	{
		Subsystem->AddMappingContext(InputContext, 0);
	}
}

void ABlackbirdPlayerController::InitializeCursor()
{
	bShowMouseCursor = true;
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
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

void ABlackbirdPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (!IsValid(Track))
	{
		return;
	}
	PlayerCart = Track->SpawnCart();
	InPawn->AttachToActor(PlayerCart, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	PlayerCart->StartCart();
	if (ITargetingActorInterface* TargetingActor = Cast<ITargetingActorInterface>(GetPawn()))
	{
		PlayerTargetingComponent = TargetingActor->GetTargetingComponent();
		PlayerTargetingComponent->OnPlayerTargetingChangedDelegate.AddDynamic(this, &ABlackbirdPlayerController::OnPlayerTargetChanged);
	}
}

ABlackbirdTrack* ABlackbirdPlayerController::GetTrack() const
{
	return Track;
}

void ABlackbirdPlayerController::SetTrack(ABlackbirdTrack* InTrack)
{
	Track = InTrack;
}

void ABlackbirdPlayerController::Move(const FInputActionValue& Value)
{
	const FVector2D InputAxisVector = Value.Get<FVector2D>();
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ControlledPawn->GetActorUpVector(), InputAxisVector.Y);
		ControlledPawn->AddMovementInput(ControlledPawn->GetActorRightVector(), InputAxisVector.X);
		MoveTarget.Deactivate();
	}
}

void ABlackbirdPlayerController::EndMove(const FInputActionValue& InputActionValue)
{
	if (PlayerCart && GetPawn())
	{
		MoveTarget = FMoveTarget::GetReturnToRelativeOrigin(GetPawn(), ReturnToOriginDuration, ReturnToOriginDelay);
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


void ABlackbirdPlayerController::OnPlayerTargetChanged(const AActor* Target, const ETargetingStatus& Status)
{
	switch (Status)
	{
	case ETargetingStatus::TargetingEnemy:
		CurrentMouseCursor = EMouseCursor::Type::Crosshairs;
		break;
	default:
		CurrentMouseCursor = EMouseCursor::Type::Default;
		break;
	}
}
