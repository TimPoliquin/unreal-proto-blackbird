// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BlackbirdPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/BlackbirdAbilitySystemComponent.h"
#include "Components/SplineComponent.h"
#include "Net/UnrealNetwork.h"
#include "Player/BlackbirdPlayerState.h"
#include "Player/PlayerTargetingComponent.h"
#include "Character/MoveTarget.h"
#include "Targeting/TargetingActorInterface.h"
#include "Track/BlackbirdTrackFollowingComponent.h"
#include "Track/TrackFollowingActorInterface.h"


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
	// InitializeCursor();
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
	FInputModeGameOnly InputModeData;
	InputModeData.SetConsumeCaptureMouseDown(false);
	SetInputMode(InputModeData);
	// center the mouse on the screen
	const UGameViewportClient* GameViewportClient = GEngine->GetWorldFromContextObjectChecked(this)->GetGameViewport();
	if (!GameViewportClient->Viewport || !GameViewportClient->Viewport->IsForegroundWindow())
	{
		return;
	}
	FVector2D ViewportSize;
	GEngine->GameViewport->GetViewportSize(ViewportSize);
	const FVector2D CenterPosition = ViewportSize / 2;
	GameViewportClient->Viewport->SetMouse(CenterPosition.X, CenterPosition.Y);
}

void ABlackbirdPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this,
		                                   &ABlackbirdPlayerController::Move);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this,
		                                   &ABlackbirdPlayerController::EndMove);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this,
		                                   &ABlackbirdPlayerController::Look);
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

bool ABlackbirdPlayerController::OnPossession_SetTrack(APawn* InPawn) const
{
	if (!IsValid(Track))
	{
		return true;
	}
	if (const ITrackFollowingActorInterface* TrackFollowingPawn = Cast<ITrackFollowingActorInterface>(InPawn))
	{
		TrackFollowingPawn->GetTrackFollowingComponent()->SetTrack(Track);
		TrackFollowingPawn->GetTrackFollowingComponent()->Activate(true);
	}
	return false;
}

void ABlackbirdPlayerController::OnPossession_SetupTargeting(APawn* InPawn)
{
	if (const ITargetingActorInterface* TargetingActor = Cast<ITargetingActorInterface>(InPawn))
	{
		PlayerTargetingComponent = TargetingActor->GetTargetingComponent();
		PlayerTargetingComponent->OnPlayerTargetingChangedDelegate.AddDynamic(
			this, &ABlackbirdPlayerController::OnPlayerTargetChanged);
	}
}

void ABlackbirdPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	// NOTE: this is server-side only!
	OnPossession_SetTrack(InPawn);
	OnPossession_SetupTargeting(InPawn);
}

void ABlackbirdPlayerController::AcknowledgePossession(APawn* InPawn)
{
	Super::AcknowledgePossession(InPawn);
	OnPossession_SetTrack(InPawn);
	OnPossession_SetupTargeting(InPawn);
}

USplineComponent* ABlackbirdPlayerController::GetTrack() const
{
	return Track;
}

void ABlackbirdPlayerController::SetTrack(USplineComponent* InTrack)
{
	Track = InTrack;
}

void ABlackbirdPlayerController::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABlackbirdPlayerController, Track);
}

void ABlackbirdPlayerController::Move(const FInputActionValue& Value)
{
	const FVector2D InputAxisVector = Value.Get<FVector2D>();
	if (const ITrackFollowingActorInterface* TrackFollowingActor = Cast<ITrackFollowingActorInterface>(GetPawn()))
	{
		TrackFollowingActor->GetTrackFollowingComponent()->AddMovementInput(InputAxisVector);
	}
	else if (APawn* ControlledPawn = Cast<APawn>(GetPawn()))
	{
		ControlledPawn->AddMovementInput(ControlledPawn->GetActorUpVector(), InputAxisVector.Y);
		ControlledPawn->AddMovementInput(ControlledPawn->GetActorRightVector(), InputAxisVector.X);
		MoveTarget.Deactivate();
	}
}

void ABlackbirdPlayerController::EndMove(const FInputActionValue& InputActionValue)
{
	if (const ITrackFollowingActorInterface* TrackFollowingActor = Cast<ITrackFollowingActorInterface>(GetPawn()))
	{
		TrackFollowingActor->GetTrackFollowingComponent()->ClearMovementInput();
	}
}

void ABlackbirdPlayerController::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	// add yaw and pitch input to controller
	AddYawInput(LookAxisVector.X);
	AddPitchInput(LookAxisVector.Y);
}

void ABlackbirdPlayerController::AbilityInputTagPressed(const FGameplayTag InputTag)
{
	if (UBlackbirdAbilitySystemComponent* BlackbirdAbilitySystemComponent = GetPlayerState<ABlackbirdPlayerState>()->
		GetBlackbirdAbilitySystemComponent())
	{
		BlackbirdAbilitySystemComponent->AbilityInputTagPressed(InputTag);
	}
}

void ABlackbirdPlayerController::AbilityInputTagReleased(const FGameplayTag InputTag)
{
	if (UBlackbirdAbilitySystemComponent* BlackbirdAbilitySystemComponent = GetPlayerState<ABlackbirdPlayerState>()->
		GetBlackbirdAbilitySystemComponent())
	{
		BlackbirdAbilitySystemComponent->AbilityInputTagReleased(InputTag);
	}
}

void ABlackbirdPlayerController::AbilityInputTagHeld(const FGameplayTag InputTag)
{
	if (UBlackbirdAbilitySystemComponent* LocalAbilitySystemComponent = GetPlayerState<ABlackbirdPlayerState>()->
		GetBlackbirdAbilitySystemComponent())
	{
		LocalAbilitySystemComponent->AbilityInputTagHeld(InputTag);
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
