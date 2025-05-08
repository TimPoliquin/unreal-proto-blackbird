// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/PlayerController.h"
#include "Input/BlackbirdInputConfiguration.h"
#include "BlackbirdPlayerController.generated.h"

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

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UBlackbirdInputConfiguration> InputConfig;
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> InputContext;
	UPROPERTY(EditAnywhere, Category="Input|Movement")
	TObjectPtr<UInputAction> MoveAction;
	UPROPERTY(EditAnywhere, Category="Input|Combat")
	TObjectPtr<UInputAction> BasicAttackAction;
	UFUNCTION()
	void Move(const FInputActionValue& Value);
	UFUNCTION()
	void EndMove(const FInputActionValue& InputActionValue);
	UFUNCTION()
	void AbilityInputTagPressed(const FGameplayTag InputTag);
	UFUNCTION()
	void AbilityInputTagReleased(const FGameplayTag InputTag);
	UFUNCTION()
	void AbilityInputTagHeld(const FGameplayTag InputTag);

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
				EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, InputTag);
			}
			if (HeldFunc)
			{
				EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Triggered, Object, HeldFunc, InputTag);
			}
		}
	}
}
