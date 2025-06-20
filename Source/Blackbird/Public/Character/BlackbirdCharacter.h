// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterInterface.h"
#include "AbilitySystemInterface.h"
#include "SocketInterface.h"
#include "GameplayTagContainer.h"
#include "AbilitySystem/BlackbirdAbilitySystemDelegates.h"
#include "AbilitySystem/Attribute/BlackbirdAttributeSetTypes.h"
#include "AbilitySystem/Damage/DamageableInterface.h"
#include "GameFramework/Character.h"
#include "Targeting/TargetableInterface.h"
#include "Track/TrackFollowingActorInterface.h"
#include "BlackbirdCharacter.generated.h"

class UBlackbirdTrackFollowingComponent;
class UGameplayEffect;
class UBlackbirdAttributeSet;
class UBlackbirdAbilitySystemComponent;
class UAbilitySystemComponent;
class UBlackbirdAbilityAssignment;
class UInputComponent;
struct FDamageEvent;


UCLASS()
class BLACKBIRD_API ABlackbirdCharacter : public ACharacter, public ICharacterInterface, public IAbilitySystemInterface,
                                          public IDamageableInterface,
                                          public ITrackFollowingActorInterface, public ITargetableInterface,
                                          public ISocketInterface
{
	GENERATED_BODY()

public:
	ABlackbirdCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(
		float DamageAmount,
		const FDamageEvent& DamageEvent,
		AController* EventInstigator,
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

	/** Start CharacterInterface **/
	virtual void SetFacingDirection(const FVector& Direction) override;
	/** End CharacterInterface **/

	/** Start ITargetableInterface **/
	virtual void Mark_Implementation() override;
	virtual void Unmark_Implementation() override;
	/** End ITargetableInterface **/

	/** Start DamageableInterface **/
	virtual FOnDamageSignature& GetOnDamageDelegate() override;
	virtual bool CanBeDamagedByInstigatorTag(const FName& InstigatorTag) const override;
	virtual bool IsAlive() const override;
	virtual bool IsDead() const override;
	/** End DamageableInterface **/

	/** Start TrackFollowingInterface **/
	virtual UBlackbirdTrackFollowingComponent* GetTrackFollowingComponent() const override;
	/** End TrackFollowingInterface **/

	/** Start ISocketInterface **/
	virtual FVector GetSocketLocation(const FGameplayTag& SocketTag) const override;
	virtual FRotator GetSocketRotation(const FGameplayTag& SocketTag) const override;
	/** End ISocketInterface **/

	UPROPERTY(BlueprintAssignable)
	FBlackbirdAbilitySystemReadySignature OnAbilitySystemReadyDelegate;

protected:
	virtual void BeginPlay() override;
	void InitAbilitySystem(AActor* OwnerActor, UBlackbirdAbilitySystemComponent* InAbilitySystemComponent);
	void InitDefaultAbilities();
	UFUNCTION(BlueprintImplementableEvent)
	void OnTriggerOverheat();
	void InitDefaultAttributes();
	UFUNCTION()
	virtual void OnReceivedDamage(const FOnReceivedDamagePayload& Payload);
	UFUNCTION()
	virtual void OnAbilitySystemReady(UBlackbirdAbilitySystemComponent* BlackbirdAbilitySystemComponent);
	UFUNCTION(BlueprintImplementableEvent)
	void Die();

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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Movement")
	TObjectPtr<UBlackbirdTrackFollowingComponent> TrackFollowingComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Abilities")
	TArray<FName> IgnoreInstigatorTags;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Abilities")
	TMap<FGameplayTag, FName> TagToSockets;

private:
	FOnDamageSignature OnDamageDelegate;
	bool bIsAbilitySystemReady = false;
};
