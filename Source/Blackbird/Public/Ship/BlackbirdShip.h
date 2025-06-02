// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShipInterface.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/BlackbirdAbilitySystemDelegates.h"
#include "AbilitySystem/Damage/DamageableInterface.h"
#include "GameFramework/Character.h"
#include "BlackbirdShip.generated.h"

class UMVVM_ShipAttributes;
class UGameplayEffect;
class UBlackbirdAttributeSet;
class UBlackbirdAbilitySystemComponent;
class UAbilitySystemComponent;
class UBlackbirdShipMovementComponent;
class UBlackbirdAbilityAssignment;
class UFloatingPawnMovement;
class UBoxComponent;
struct FBlackbirdAbilityAssignmentRow;

UCLASS()
class BLACKBIRD_API ABlackbirdShip : public ACharacter, public IShipInterface, public IAbilitySystemInterface, public IDamageableInterface
{
	GENERATED_BODY()

public:
	ABlackbirdShip();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(
		float DamageAmount,
		const struct FDamageEvent& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser
	) override;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UFUNCTION(BlueprintCallable, BlueprintPure)
	virtual UBlackbirdAbilitySystemComponent* GetBlackbirdAbilitySystemComponent() const;
	UFUNCTION(BlueprintCallable, BlueprintPure)
	virtual UBlackbirdAttributeSet* GetBlackbirdAttributeSet() const;
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsAbilitySystemReady() const;

	/** Start ShipInterface **/
	virtual void SetFacingDirection(const FVector& Direction) override;
	/** End ShipInterface **/

	/** Start DamageableInterface **/
	virtual FOnDamageSignature& GetOnDamageDelegate() override;
	/** End DamageableInterface **/
	UPROPERTY(BlueprintAssignable)
	FBlackbirdAbilitySystemReadySignature OnAbilitySystemReadyDelegate;

protected:
	virtual void BeginPlay() override;
	void InitAbilitySystem(AActor* OwnerActor, UBlackbirdAbilitySystemComponent* InAbilitySystemComponent);
	void InitDefaultAbilities();
	void InitDefaultAttributes();
	UFUNCTION()
	virtual void OnAbilitySystemReady(UBlackbirdAbilitySystemComponent* BlackbirdAbilitySystemComponent);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Abilities")
	TObjectPtr<UBlackbirdAbilityAssignment> StartingAbilities;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Abilities")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	TObjectPtr<UBlackbirdAttributeSet> AttributeSet;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attributes")
	TArray<TSubclassOf<UGameplayEffect>> PassiveEffects;

private:
	FOnDamageSignature OnDamageDelegate;
	bool bIsAbilitySystemReady = false;
};
