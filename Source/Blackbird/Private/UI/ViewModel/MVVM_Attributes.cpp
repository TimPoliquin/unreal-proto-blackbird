// Copyright Alien Shores 2025


#include "UI/ViewModel/MVVM_Attributes.h"

#include "AbilitySystem/BlackbirdAbilitySystemComponent.h"
#include "AbilitySystem/Attribute/BlackbirdAttributeSet.h"
#include "AbilitySystem/Attribute/BlackbirdAttributeTags.h"
#include "Kismet/KismetMathLibrary.h"
#include "Character/BlackbirdCharacter.h"

UMVVM_Attributes::UMVVM_Attributes()
{
	const FBlackbirdAttributeTags& AttributeTags = FBlackbirdAttributeTags::Get();
	AddTagToAttributeSetterMap(AttributeTags.Attributes_Primary_MaxHealth, &UMVVM_Attributes::SetMaxHealth);
	AddTagToAttributeSetterMap(AttributeTags.Attributes_Primary_MaxEnergy, &UMVVM_Attributes::SetMaxEnergy);
	AddTagToAttributeSetterMap(AttributeTags.Attributes_Primary_MaxHeat, &UMVVM_Attributes::SetMaxHeat);
	AddTagToAttributeSetterMap(AttributeTags.Attributes_Vital_Health, &UMVVM_Attributes::SetHealth);
	AddTagToAttributeSetterMap(AttributeTags.Attributes_Vital_Energy, &UMVVM_Attributes::SetEnergy);
	AddTagToAttributeSetterMap(AttributeTags.Attributes_Vital_AvailableHeat, &UMVVM_Attributes::SetAvailableHeat);
}

void UMVVM_Attributes::BindDependencies(const ABlackbirdCharacter* Owner)
{
	if (IsValid(Owner))
	{
		if (const UBlackbirdAttributeSet* AttributeSet = Owner->GetBlackbirdAttributeSet())
		{
			UE_LOG(
				LogTemp,
				Warning,
				TEXT("[%s %s] Initializing Attribute ViewModel for [%s]"),
				*(Owner->HasAuthority() ? FString("Server") : FString("Client")),
				*GetName(),
				*Owner->GetName()
			)
			InitializeValues(Owner, AttributeSet);
			if (UBlackbirdAbilitySystemComponent* AbilitySystemComponent = Owner->GetBlackbirdAbilitySystemComponent())
			{
				for (auto Pair : TagToAttributeSetterMap)
				{
					AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
						AttributeSet->GetAttributeByTag(Pair.Key)).AddLambda(
						[Pair](const FOnAttributeChangeData& Data)
						{
							Pair.Value(Data.NewValue);
						}
					);
				}
			}
		}
	}
}

float UMVVM_Attributes::GetHealth() const
{
	return Health;
}

void UMVVM_Attributes::SetHealth(const float InHealth)
{
	UE_MVVM_SET_PROPERTY_VALUE(Health, InHealth);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetHealthPercentage);
}

float UMVVM_Attributes::GetMaxHealth() const
{
	return MaxHealth;
}

void UMVVM_Attributes::SetMaxHealth(const float InMaxHealth)
{
	UE_MVVM_SET_PROPERTY_VALUE(MaxHealth, InMaxHealth);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetHealthPercentage);
}

float UMVVM_Attributes::GetEnergy() const
{
	return Energy;
}

void UMVVM_Attributes::SetEnergy(const float InEnergy)
{
	UE_MVVM_SET_PROPERTY_VALUE(Energy, InEnergy);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetEnergyPercentage);
}

float UMVVM_Attributes::GetMaxEnergy() const
{
	return MaxEnergy;
}

void UMVVM_Attributes::SetMaxEnergy(const float InMaxEnergy)
{
	UE_MVVM_SET_PROPERTY_VALUE(MaxEnergy, InMaxEnergy);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetEnergyPercentage);
}

float UMVVM_Attributes::GetAvailableHeat() const
{
	return AvailableHeat;
}

void UMVVM_Attributes::SetAvailableHeat(const float InHeat)
{
	UE_MVVM_SET_PROPERTY_VALUE(AvailableHeat, InHeat);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetHeatPercentage);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetHeatAmount);
}

float UMVVM_Attributes::GetMaxHeat() const
{
	return MaxHeat;
}

void UMVVM_Attributes::SetMaxHeat(const float InMaxHeat)
{
	UE_MVVM_SET_PROPERTY_VALUE(MaxHeat, InMaxHeat);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetHeatPercentage);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetHeatAmount);
}

float UMVVM_Attributes::GetHealthPercentage() const
{
	return UKismetMathLibrary::SafeDivide(Health, MaxHealth);
}

float UMVVM_Attributes::GetEnergyPercentage() const
{
	return UKismetMathLibrary::SafeDivide(Energy, MaxEnergy);
}

float UMVVM_Attributes::GetHeatPercentage() const
{
	return UKismetMathLibrary::SafeDivide(MaxHeat - AvailableHeat, MaxHeat);
}

float UMVVM_Attributes::GetHeatAmount() const
{
	return MaxHeat - AvailableHeat;
}

void UMVVM_Attributes::OnReceivedDamage(const float DamageAmount, const bool bFatal)
{
	UE_LOG(LogTemp, Warning, TEXT("[%s] Received damage!"), *GetName())
	if (bFatal)
	{
	}
}

void UMVVM_Attributes::AddTagToAttributeSetterMap(
	const FGameplayTag& Tag,
	TFunction<void(UMVVM_Attributes*, const float)> Setter
)
{
	TagToAttributeSetterMap.Add(
		Tag,
		[this, Setter](const float Value)
		{
			Setter(this, Value);
		}
	);
}

void UMVVM_Attributes::InitializeValues(const ABlackbirdCharacter* Owner, const UBlackbirdAttributeSet* AttributeSet)
{
	SetMaxHealth(AttributeSet->GetMaxHealth());
	SetHealth(AttributeSet->GetHealth());
	SetMaxEnergy(AttributeSet->GetMaxEnergy());
	SetEnergy(AttributeSet->GetEnergy());
	SetMaxHeat(AttributeSet->GetMaxHeat());
	SetAvailableHeat(AttributeSet->GetAvailableHeat());
}
