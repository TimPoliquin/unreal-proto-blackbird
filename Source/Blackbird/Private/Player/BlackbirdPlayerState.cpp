// Copyright Alien Shores 2025


#include "Player/BlackbirdPlayerState.h"

#include "AbilitySystem/BlackbirdAbilitySystemComponent.h"
#include "AbilitySystem/Attribute/BlackbirdAttributeSet.h"

ABlackbirdPlayerState::ABlackbirdPlayerState()
{
	SetNetUpdateFrequency(100.f);
	BlackbirdAbilitySystemComponent = CreateDefaultSubobject<UBlackbirdAbilitySystemComponent>(TEXT("Ability System Component"));
	BlackbirdAbilitySystemComponent->SetIsReplicated(true);
	BlackbirdAbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	BlackbirdAttributeSet = CreateDefaultSubobject<UBlackbirdAttributeSet>(TEXT("Attribute Set"));
}

UBlackbirdAbilitySystemComponent* ABlackbirdPlayerState::GetBlackbirdAbilitySystemComponent()
{
	return BlackbirdAbilitySystemComponent;
}

UBlackbirdAttributeSet* ABlackbirdPlayerState::GetBlackbirdAttributeSet()
{
	return BlackbirdAttributeSet;
}

void ABlackbirdPlayerState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}
