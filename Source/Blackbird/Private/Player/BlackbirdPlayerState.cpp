// Copyright Alien Shores 2025


#include "Player/BlackbirdPlayerState.h"

#include "AbilitySystem/BlackbirdAbilitySystemComponent.h"

ABlackbirdPlayerState::ABlackbirdPlayerState()
{
	SetNetUpdateFrequency(100.f);
	BlackbirdAbilitySystemComponent = CreateDefaultSubobject<UBlackbirdAbilitySystemComponent>(TEXT("Ability System Component"));
	BlackbirdAbilitySystemComponent->SetIsReplicated(true);
	BlackbirdAbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

UBlackbirdAbilitySystemComponent* ABlackbirdPlayerState::GetBlackbirdAbilitySystemComponent()
{
	return BlackbirdAbilitySystemComponent;
}

void ABlackbirdPlayerState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}
