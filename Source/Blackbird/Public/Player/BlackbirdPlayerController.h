// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "Game/BlackbirdPlayerStart.h"
#include "GameFramework/PlayerController.h"
#include "Input/BlackbirdInputConfiguration.h"
#include "Character/MoveTarget.h"
#include "BlackbirdPlayerController.generated.h"

class USplineComponent;
class UPlayerTargetingComponent;
class ABlackbirdTrack;
struct FInputActionValue;
struct FGameplayTag;
class UBlackbirdInputConfiguration;
class UInputAction;
class UInputMappingContext;

/**
 * 
 */
UCLASS()
class BLACKBIRD_API ABlackbirdPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ABlackbirdPlayerController();
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	USplineComponent* GetTrack() const;
	UFUNCTION(BlueprintCallable)
	void SetTrack(USplineComponent* InTrack);
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	bool OnPossession_SetTrack(APawn* InPawn) const;
	void OnPossession_SetupTargeting(APawn* InPawn);
	virtual void OnPossess(APawn* InPawn) override;
	virtual void AcknowledgePossession(class APawn* InPawn) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Replicated, Category="Track")
	TObjectPtr<USplineComponent> Track;

private:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UBlackbirdInputConfiguration> InputConfig;
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> InputContext;
	UPROPERTY(EditAnywhere, Category="Input|Camera")
	TObjectPtr<UInputAction> LookAction;
	UPROPERTY(EditAnywhere, Category="Input|Movement")
	TObjectPtr<UInputAction> MoveAction;
	UPROPERTY(EditDefaultsOnly, Category="Input|Movement")
	float ReturnToOriginDuration = 2.f;
	UPROPERTY(EditDefaultsOnly, Category="Input|Movement")
	float ReturnToOriginDelay = .5f;
	FMoveTarget MoveTarget;
	/** Set during player possession -- not managed by the PlayerController!*/
	UPROPERTY()
	TObjectPtr<UPlayerTargetingComponent> PlayerTargetingComponent;
	UFUNCTION()
	void Move(const FInputActionValue& Value);
	UFUNCTION()
	void EndMove(const FInputActionValue& InputActionValue);
	UFUNCTION()
	void Look(const FInputActionValue& Value);
	UFUNCTION()
	void AbilityInputTagPressed(const FGameplayTag InputTag);
	UFUNCTION()
	void AbilityInputTagReleased(const FGameplayTag InputTag);
	UFUNCTION()
	void AbilityInputTagHeld(const FGameplayTag InputTag);

	void InitializeCursor();
	UFUNCTION()
	void OnPlayerTargetChanged(const AActor* Target, const ETargetingStatus& Status);

	template <
		class UserClass,
		typename PressedFuncType,
		typename ReleasedFuncType,
		typename HeldFuncType
	>
	static void BindAbilityActions(
		const UBlackbirdInputConfiguration* InputConfig,
		UEnhancedInputComponent* EnhancedInputComponent,
		UserClass* Object,
		PressedFuncType PressedFunc,
		ReleasedFuncType ReleasedFunc,
		HeldFuncType HeldFunc
	);
};

template <class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
void ABlackbirdPlayerController::BindAbilityActions(
	const UBlackbirdInputConfiguration* InputConfig,
	UEnhancedInputComponent* EnhancedInputComponent,
	UserClass* Object,
	PressedFuncType PressedFunc,
	ReleasedFuncType ReleasedFunc,
	HeldFuncType HeldFunc
)
{
	check(InputConfig);
	for (const auto& [InputAction, InputTag] : InputConfig->GetAbilityInputActions())
	{
		if (InputAction && InputTag.IsValid())
		{
			if (PressedFunc)
			{
				EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Started, Object, PressedFunc, InputTag);
			}
			if (ReleasedFunc)
			{
				EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Completed, Object, ReleasedFunc,
				                                   InputTag);
			}
			if (HeldFunc)
			{
				EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Triggered, Object, HeldFunc, InputTag);
			}
		}
	}
}
