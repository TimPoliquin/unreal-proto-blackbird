// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BlackbirdCharacter.h"

#include "AbilitySystem/BlackbirdAbilitySystemComponent.h"
#include "AbilitySystem/BlackbirdAbilitySystemLibrary.h"
#include "AbilitySystem/Ability/BlackbirdAbilityAssignment.h"
#include "AbilitySystem/Attribute/BlackbirdAttributeSet.h"
#include "Components/CapsuleComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Track/BlackbirdTrackFollowingComponent.h"


ABlackbirdCharacter::ABlackbirdCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	UCharacterMovementComponent* CharacterMovementComponent = Cast<UCharacterMovementComponent>(GetMovementComponent());
	CharacterMovementComponent->GravityScale = 0.f;
	CharacterMovementComponent->SetMovementMode(MOVE_Flying);
	TrackFollowingComponent = CreateDefaultSubobject<UBlackbirdTrackFollowingComponent>(
		TEXT("Track Following Component"));
}

void ABlackbirdCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ABlackbirdCharacter::InitAbilitySystem(
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

void ABlackbirdCharacter::InitDefaultAbilities()
{
	if (StartingAbilities == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Starting Abilities is null"));
		return;
	}
	UE_LOG(LogTemp, Display, TEXT("Adding Starting Abilities"));
	GetBlackbirdAbilitySystemComponent()->AddAbilities(StartingAbilities->GetAbilityAssignments());
}

void ABlackbirdCharacter::InitDefaultAttributes()
{
	UBlackbirdAbilitySystemLibrary::ApplyEffectToSelf(this, DefaultPrimaryAttributes);
	UBlackbirdAbilitySystemLibrary::ApplyEffectToSelf(this, DefaultVitalAttributes);
	for (const TSubclassOf<UGameplayEffect>& PassiveEffect : PassiveEffects)
	{
		UBlackbirdAbilitySystemLibrary::ApplyEffectToSelf(this, PassiveEffect);
	}
}

void ABlackbirdCharacter::OnReceivedDamage(const FOnReceivedDamagePayload& Payload)
{
	if (Payload.bFatal)
	{
		Die();
	}
}

void ABlackbirdCharacter::OnAbilitySystemReady(UBlackbirdAbilitySystemComponent* BlackbirdAbilitySystemComponent)
{
	InitDefaultAbilities();
	InitDefaultAttributes();
	GetBlackbirdAttributeSet()->OnTriggerOverheat.AddDynamic(this, &ABlackbirdCharacter::OnTriggerOverheat);
	GetBlackbirdAttributeSet()->OnReceivedDamage.AddDynamic(this, &ABlackbirdCharacter::OnReceivedDamage);
}

void ABlackbirdCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABlackbirdCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float ABlackbirdCharacter::TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator,
                                      AActor* DamageCauser)
{
	const float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	OnDamageDelegate.Broadcast(Damage);
	return Damage;
}

UAbilitySystemComponent* ABlackbirdCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UBlackbirdAbilitySystemComponent* ABlackbirdCharacter::GetBlackbirdAbilitySystemComponent() const
{
	return Cast<UBlackbirdAbilitySystemComponent>(AbilitySystemComponent);
}

UBlackbirdAttributeSet* ABlackbirdCharacter::GetBlackbirdAttributeSet() const
{
	return AttributeSet;
}

bool ABlackbirdCharacter::IsAbilitySystemReady() const
{
	return bIsAbilitySystemReady;
}

void ABlackbirdCharacter::SetFacingDirection(const FVector& Direction)
{
}

void ABlackbirdCharacter::Mark_Implementation()
{
	ITargetableInterface::Mark_Implementation();
}

void ABlackbirdCharacter::Unmark_Implementation()
{
	ITargetableInterface::Unmark_Implementation();
}

FOnDamageSignature& ABlackbirdCharacter::GetOnDamageDelegate()
{
	return OnDamageDelegate;
}

bool ABlackbirdCharacter::CanBeDamagedByInstigatorTag(const FName& InstigatorTag) const
{
	return !IgnoreInstigatorTags.Contains(InstigatorTag);
}

bool ABlackbirdCharacter::IsAlive() const
{
	return GetBlackbirdAttributeSet()->IsAlive();
}

bool ABlackbirdCharacter::IsDead() const
{
	return GetBlackbirdAttributeSet()->IsDead();
}

UBlackbirdTrackFollowingComponent* ABlackbirdCharacter::GetTrackFollowingComponent() const
{
	return TrackFollowingComponent;
}

FVector ABlackbirdCharacter::GetSocketLocation(const FGameplayTag& SocketTag) const
{
	if (TagToSockets.Contains(SocketTag))
	{
		return GetMesh()->GetSocketByName(TagToSockets[SocketTag])->GetSocketLocation(GetMesh());
	}
	return GetActorLocation();
}

FRotator ABlackbirdCharacter::GetSocketRotation(const FGameplayTag& SocketTag) const
{
	if (TagToSockets.Contains(SocketTag))
	{
		return GetMesh()->GetSocketByName(TagToSockets[SocketTag])->GetSocketTransform(GetMesh()).Rotator();
	}
	return GetActorRotation();
}
