// Copyright Alien Shores 2025

#pragma once

#include "CoreMinimal.h"
#include "ProjectileInterface.h"
#include "AbilitySystem/Effect/BlackbirdDamageEffectParams.h"
#include "BlackbirdProjectileActor.generated.h"

class FLifetimeProperty;
class UCapsuleComponent;
class UProjectileMovementComponent;
class UNiagaraSystem;


UCLASS()
class BLACKBIRD_API ABlackbirdProjectileActor : public AActor, public IProjectileInterface
{
	GENERATED_BODY()

public:
	ABlackbirdProjectileActor();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	void SetDamageEffectParams(FBlackbirdDamageEffectParams& Params);
	virtual void Tick(float DeltaTime) override;
	/**
	 * Start IProjectileInterface
	 */
	virtual UProjectileMovementComponent* GetProjectileMovementComponent_Implementation() const override;
	virtual void Repel_Implementation(AActor* NewOwner, const FHitResult& NewTarget, const float RepelAngle = 90.f, const float BaseDamageMultiplier = 1.f) override;
	/**
	 * End IProjectileInterface
	 */

protected:
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Projectile")
	FVector GetImpactDirection(const AActor* HitActor) const;
	UFUNCTION(BlueprintCallable, Category="Projectile|Sound")
	void PlayTravelSound();
	UFUNCTION(BlueprintCallable, Category="Projectile|Sound")
	void PlayImpactEffect();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Projectile")
	float MaxLifetime = 10.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Projectile")
	float HomingLifetime = 1.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Projectile")
	TObjectPtr<UCapsuleComponent> CapsuleComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Projectile")
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Projectile")
	TObjectPtr<UProjectileMovementComponent> ProjectileComponent;
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true), Replicated)
	FBlackbirdDamageEffectParams DamageEffectParams;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Projectile")
	TObjectPtr<USoundBase> TravelSound;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Projectile|Impact")
	TObjectPtr<USoundBase> ImpactSound;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Projectile|Impact")
	TObjectPtr<UNiagaraSystem> ImpactEffect;

private:
	UFUNCTION()
	void OnCollisionBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool BFromSweep,
		const FHitResult& SweepResult
	);

	UPROPERTY()
	TObjectPtr<UAudioComponent> TravelSoundComponent;
	bool bHit = false;
	float Lifetime = 0.f;
};
