// Fill out your copyright notice in the Description page of Project Settings.


#include "Ship/BlackbirdShip.h"

#include "AbilitySystem/BlackbirdAbilitySystemComponent.h"
#include "AbilitySystem/BlackbirdAbilitySystemLibrary.h"
#include "AbilitySystem/Ability/BlackbirdAbilityAssignment.h"
#include "AbilitySystem/Attribute/BlackbirdAttributeSet.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Track/BlackbirdTrackFollowingComponent.h"


ABlackbirdShip::ABlackbirdShip()
{
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	UCharacterMovementComponent* CharacterMovementComponent = Cast<UCharacterMovementComponent>(GetMovementComponent());
	CharacterMovementComponent->GravityScale = 0.f;
	CharacterMovementComponent->SetMovementMode(MOVE_Flying);
	TrackFollowingComponent = CreateDefaultSubobject<UBlackbirdTrackFollowingComponent>(TEXT("Track Following Component"));
}

void ABlackbirdShip::BeginPlay()
{
	Super::BeginPlay();
}

void ABlackbirdShip::InitAbilitySystem(
	AActor* OwnerActor,
	UBlackbirdAbilitySystemComponent* InAbilitySystemComponent
)
{
	AbilitySystemComponent = Cast<UAbilitySystemComponent>(InAbilitySystemComponent);
	AbilitySystemComponent->InitAbilityActorInfo(OwnerActor, this);
	OnAbilitySystemReady(InAbilitySystemComponent);
	bIsAbilitySystemReady = true;
	OnAbilitySystemReadyDelegate.Broadcast(InAbilitySystemComponent);
}

void ABlackbirdShip::InitDefaultAbilities()
{
	if (StartingAbilities == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Starting Abilities is null"));
		return;
	}
	UE_LOG(LogTemp, Display, TEXT("Adding Starting Abilities"));
	GetBlackbirdAbilitySystemComponent()->AddAbilities(StartingAbilities->GetAbilityAssignments());
}

void ABlackbirdShip::InitDefaultAttributes()
{
	UBlackbirdAbilitySystemLibrary::ApplyEffectToSelf(this, DefaultPrimaryAttributes);
	UBlackbirdAbilitySystemLibrary::ApplyEffectToSelf(this, DefaultVitalAttributes);
	for (const TSubclassOf<UGameplayEffect>& PassiveEffect : PassiveEffects)
	{
		UBlackbirdAbilitySystemLibrary::ApplyEffectToSelf(this, PassiveEffect);
	}
}

void ABlackbirdShip::OnAbilitySystemReady(UBlackbirdAbilitySystemComponent* BlackbirdAbilitySystemComponent)
{
	InitDefaultAbilities();
	InitDefaultAttributes();
	GetBlackbirdAttributeSet()->OnTriggerOverheat.AddDynamic(this, &ABlackbirdShip::OnTriggerOverheat);
}

void ABlackbirdShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABlackbirdShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float ABlackbirdShip::TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	OnDamageDelegate.Broadcast(Damage);
	return Damage;
}

UAbilitySystemComponent* ABlackbirdShip::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UBlackbirdAbilitySystemComponent* ABlackbirdShip::GetBlackbirdAbilitySystemComponent() const
{
	return Cast<UBlackbirdAbilitySystemComponent>(AbilitySystemComponent);
}

UBlackbirdAttributeSet* ABlackbirdShip::GetBlackbirdAttributeSet() const
{
	return AttributeSet;
}

bool ABlackbirdShip::IsAbilitySystemReady() const
{
	return bIsAbilitySystemReady;
}

void ABlackbirdShip::SetFacingDirection(const FVector& Direction)
{
}

void ABlackbirdShip::Mark_Implementation()
{
	ITargetableInterface::Mark_Implementation();
}

void ABlackbirdShip::Unmark_Implementation()
{
	ITargetableInterface::Unmark_Implementation();
}

FOnDamageSignature& ABlackbirdShip::GetOnDamageDelegate()
{
	return OnDamageDelegate;
}

bool ABlackbirdShip::CanBeDamagedByInstigatorTag(const FName& InstigatorTag) const
{
	return !IgnoreInstigatorTags.Contains(InstigatorTag);
}

bool ABlackbirdShip::IsAlive() const
{
	return GetBlackbirdAttributeSet()->IsAlive();
}

bool ABlackbirdShip::IsDead() const
{
	return GetBlackbirdAttributeSet()->IsDead();
}

UBlackbirdTrackFollowingComponent* ABlackbirdShip::GetTrackFollowingComponent() const
{
	return TrackFollowingComponent;
}
