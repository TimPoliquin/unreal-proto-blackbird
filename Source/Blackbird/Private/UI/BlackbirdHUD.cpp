// Copyright Alien Shores 2025


#include "UI/BlackbirdHUD.h"

#include "Player/BlackbirdPlayerCharacter.h"
#include "Character/BlackbirdCharacter.h"
#include "UI/ViewModel/MVVM_PlayerTargeting.h"
#include "UI/ViewModel/MVVM_Attributes.h"
#include "UI/Widget/HUD/BlackbirdGameHUDWidget.h"

UMVVM_Attributes* ABlackbirdHUD::GetAttributesViewModel() const
{
	return AttributesViewModel;
}

UMVVM_PlayerTargeting* ABlackbirdHUD::GetPlayerTargetingViewModel() const
{
	return PlayerTargetingViewModel;
}

void ABlackbirdHUD::BeginPlay()
{
	Super::BeginPlay();
	checkf(AttributesViewModelClass, TEXT("[%s] AttributesViewModelClass must be specified"), *GetName());
	checkf(PlayerTargetingViewModelClass, TEXT("[%s] PlayerTargetingViewModelClass must be specified"), *GetName());
	checkf(GameHUDWidgetClass, TEXT("[%s] GameHUDWidgetClass must be specified"), *GetName());
	AttributesViewModel = NewObject<UMVVM_Attributes>(this, AttributesViewModelClass);
	PlayerTargetingViewModel = NewObject<UMVVM_PlayerTargeting>(this, PlayerTargetingViewModelClass);
	GameHUDWidget = CreateWidget<UBlackbirdGameHUDWidget>(GetWorld(), GameHUDWidgetClass);
	GameHUDWidget->AddToViewport();
	if (ABlackbirdCharacter* PlayerCharacter = Cast<ABlackbirdCharacter>(GetOwningPawn()))
	{
		if (PlayerCharacter->IsAbilitySystemReady())
		{
			OnAbilitySystemReady(PlayerCharacter->GetBlackbirdAbilitySystemComponent());
		}
		else
		{
			PlayerCharacter->OnAbilitySystemReadyDelegate.AddDynamic(this, &ABlackbirdHUD::OnAbilitySystemReady);
		}
	}
}

void ABlackbirdHUD::OnAbilitySystemReady(UBlackbirdAbilitySystemComponent* BlackbirdAbilitySystemComponent)
{
	if (const ABlackbirdCharacter* BlackbirdCharacter = Cast<ABlackbirdCharacter>(GetOwningPawn()))
	{
		AttributesViewModel->BindDependencies(BlackbirdCharacter);
	}
	if (const ABlackbirdPlayerCharacter* PlayerCharacter = Cast<ABlackbirdPlayerCharacter>(GetOwningPawn()))
	{
		PlayerTargetingViewModel->BindDependencies(PlayerCharacter);
	}
}
