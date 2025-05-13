// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShipInterface.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/BlackbirdAbilitySystemDelegates.h"
#include "GameFramework/Character.h"
#include "BlackbirdShip.generated.h"

class UBlackbirdAbilitySystemComponent;
class UAbilitySystemComponent;
class UBlackbirdShipMovementComponent;
class UBlackbirdAbilityAssignment;
class UFloatingPawnMovement;
class UBoxComponent;
struct FBlackbirdAbilityAssignmentRow;

UCLASS()
class BLACKBIRD_API ABlackbirdShip : public ACharacter, public IShipInterface, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ABlackbirdShip();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UBlackbirdAbilitySystemComponent* GetBlackbirdAbilitySystemComponent();

	/** Start ShipInterface **/
	virtual void SetFacingDirection(const FVector& Direction) override;
	/** End ShipInterface **/

	FBlackbirdAbilitySystemReadySignature OnAbilitySystemReadyDelegate;

protected:
	virtual void BeginPlay() override;
	void InitAbilitySystem(AActor* OwnerActor, UBlackbirdAbilitySystemComponent* InAbilitySystemComponent);
	void InitDefaultAbilities();
	UFUNCTION()
	virtual void OnAbilitySystemReady(UBlackbirdAbilitySystemComponent* BlackbirdAbilitySystemComponent);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Abilities")
	TObjectPtr<UBlackbirdAbilityAssignment> StartingAbilities;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Abilities")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
};
