// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ship/BlackbirdShip.h"
#include "Targeting/TargetingActorInterface.h"
#include "BlackbirdPlayerShip.generated.h"

class UPlayerTargetingComponent;
class ABlackbirdPlayerState;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class BLACKBIRD_API ABlackbirdPlayerShip : public ABlackbirdShip, public ITargetingActorInterface
{
	GENERATED_BODY()

public:
	ABlackbirdPlayerShip();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void OnRep_PlayerState() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual UBlackbirdAbilitySystemComponent* GetBlackbirdAbilitySystemComponent() const override;
	ABlackbirdPlayerState* GetBlackbirdPlayerState() const;

	/** ITargetingActorInterface start **/
	virtual UPlayerTargetingComponent* GetTargetingComponent() const override;
	/** ITargetingActorInterface end **/


protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USpringArmComponent> SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UCameraComponent> Camera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Targeting")
	TObjectPtr<UPlayerTargetingComponent> TargetingComponent;

private:
	void InitAbilityActorInfo();
};
