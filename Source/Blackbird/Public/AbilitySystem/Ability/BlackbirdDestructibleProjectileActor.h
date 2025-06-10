// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "BlackbirdProjectileActor.h"
#include "AbilitySystem/Damage/DamageableInterface.h"
#include "Targeting/TargetableInterface.h"
#include "BlackbirdDestructibleProjectileActor.generated.h"

class UBlackbirdBasicAttributeSet;

UCLASS()
class BLACKBIRD_API ABlackbirdDestructibleProjectileActor : public ABlackbirdProjectileActor, public IDamageableInterface, public IAbilitySystemInterface,
                                                            public ITargetableInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABlackbirdDestructibleProjectileActor();

	/** Start IAbilitySystemInterface **/
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	/** End IAbilitySystemInterface **/

	/** Start IDamageableInterface **/
	virtual bool CanBeDamagedByInstigatorTag(const FName& InstigatorTag) const override;
	virtual FOnDamageSignature& GetOnDamageDelegate() override;
	virtual bool IsAlive() const override;
	virtual bool IsDead() const override;
	/** End IDamageableInterface **/

	/** Start ITargetableInterface **/
	virtual void Mark_Implementation() override
	{
	};

	virtual void Unmark_Implementation() override
	{
	};
	/** End ITargetableInterface **/


	FOnDamageSignature OnDamageDelegate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attributes")
	TSubclassOf<UGameplayEffect> SetupInitialAttributes;
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	TObjectPtr<UBlackbirdBasicAttributeSet> AttributeSet;
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UFUNCTION(BlueprintImplementableEvent)
	void Explode();

private:
	void InitializeAbilitySystem();
	UFUNCTION()
	void OnReceivedDamage(const float DamageAmount, const bool BFatal);
};
