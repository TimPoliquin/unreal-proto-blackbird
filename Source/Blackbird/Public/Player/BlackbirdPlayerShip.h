// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ship/BlackbirdShip.h"
#include "BlackbirdPlayerShip.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class BLACKBIRD_API ABlackbirdPlayerShip : public ABlackbirdShip
{
	GENERATED_BODY()

public:
	ABlackbirdPlayerShip();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USpringArmComponent> SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UCameraComponent> Camera;
};
