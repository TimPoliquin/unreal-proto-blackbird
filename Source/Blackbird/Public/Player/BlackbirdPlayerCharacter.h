// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerInterface.h"
#include "Character/BlackbirdCharacter.h"
#include "Targeting/TargetingActorInterface.h"
#include "BlackbirdPlayerCharacter.generated.h"

class UPlayerTargetingComponent;
class ABlackbirdPlayerState;
class UInputComponent;

UCLASS()
class BLACKBIRD_API ABlackbirdPlayerCharacter : public ABlackbirdCharacter, public ITargetingActorInterface,
                                                public IPlayerInterface
{
	GENERATED_BODY()

public:
	ABlackbirdPlayerCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void OnRep_PlayerState() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual UBlackbirdAbilitySystemComponent* GetBlackbirdAbilitySystemComponent() const override;
	ABlackbirdPlayerState* GetBlackbirdPlayerState() const;
	void SetPlayerCamera(ABlackbirdPlayerCamera* InPlayerCamera);


	/** ITargetingActorInterface start **/
	virtual UPlayerTargetingComponent* GetTargetingComponent() const override;
	/** ITargetingActorInterface end **/

	/** IPlayerInterface **/
	virtual UCameraComponent* GetCameraComponent() const override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Targeting")
	TObjectPtr<UPlayerTargetingComponent> TargetingComponent;

private:
	void InitAbilityActorInfo();
	TObjectPtr<ABlackbirdPlayerCamera> PlayerCamera;
};
