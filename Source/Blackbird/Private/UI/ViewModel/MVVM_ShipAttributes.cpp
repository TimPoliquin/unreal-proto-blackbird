// Copyright Alien Shores 2025


#include "UI/ViewModel/MVVM_ShipAttributes.h"

#include "AbilitySystem/Attribute/BlackbirdAttributeSet.h"
#include "AbilitySystem/Attribute/BlackbirdAttributeTags.h"
#include "Kismet/KismetMathLibrary.h"
#include "Ship/BlackbirdShip.h"

UMVVM_ShipAttributes::UMVVM_ShipAttributes()
{
	const FBlackbirdAttributeTags& AttributeTags = FBlackbirdAttributeTags::Get();
	AddTagToAttributeSetterMap(AttributeTags.Attributes_Primary_MaxHealth, &UMVVM_ShipAttributes::SetMaxHealth);
	AddTagToAttributeSetterMap(AttributeTags.Attributes_Primary_MaxEnergy, &UMVVM_ShipAttributes::SetMaxEnergy);
	AddTagToAttributeSetterMap(AttributeTags.Attributes_Primary_MaxHeat, &UMVVM_ShipAttributes::SetMaxHeat);
	AddTagToAttributeSetterMap(AttributeTags.Attributes_Vital_Health, &UMVVM_ShipAttributes::SetHealth);
	AddTagToAttributeSetterMap(AttributeTags.Attributes_Vital_Energy, &UMVVM_ShipAttributes::SetEnergy);
	AddTagToAttributeSetterMap(AttributeTags.Attributes_Vital_AvailableHeat, &UMVVM_ShipAttributes::SetAvailableHeat);
}

void UMVVM_ShipAttributes::BindDependencies(const ABlackbirdShip* Owner)
{
	if (IsValid(Owner))
	{
		if (UBlackbirdAttributeSet* AttributeSet = Owner->GetBlackbirdAttributeSet())
		{
			UE_LOG(
				LogTemp,
				Warning,
				TEXT("[%s] Initializing Attribute ViewModel for [%s]"),
				*GetName(),
				*Owner->GetName()
			)
			AttributeSet->OnAttributeChanged.AddDynamic(this, &UMVVM_ShipAttributes::OnAttributeChanged);
			AttributeSet->OnReceivedDamage.AddDynamic(this, &UMVVM_ShipAttributes::OnReceivedDamage);
			InitializeValues(Owner, AttributeSet);
		}
	}
}

float UMVVM_ShipAttributes::GetHealth() const
{
	return Health;
}

void UMVVM_ShipAttributes::SetHealth(const float InHealth)
{
	UE_MVVM_SET_PROPERTY_VALUE(Health, InHealth);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetHealthPercentage);
}

float UMVVM_ShipAttributes::GetMaxHealth() const
{
	return MaxHealth;
}

void UMVVM_ShipAttributes::SetMaxHealth(const float InMaxHealth)
{
	UE_MVVM_SET_PROPERTY_VALUE(MaxHealth, InMaxHealth);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetHealthPercentage);
}

float UMVVM_ShipAttributes::GetEnergy() const
{
	return Energy;
}

void UMVVM_ShipAttributes::SetEnergy(const float InEnergy)
{
	UE_MVVM_SET_PROPERTY_VALUE(Energy, InEnergy);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetEnergyPercentage);
}

float UMVVM_ShipAttributes::GetMaxEnergy() const
{
	return MaxEnergy;
}

void UMVVM_ShipAttributes::SetMaxEnergy(const float InMaxEnergy)
{
	UE_MVVM_SET_PROPERTY_VALUE(MaxEnergy, InMaxEnergy);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetEnergyPercentage);
}

float UMVVM_ShipAttributes::GetAvailableHeat() const
{
	return AvailableHeat;
}

void UMVVM_ShipAttributes::SetAvailableHeat(const float InHeat)
{
	UE_MVVM_SET_PROPERTY_VALUE(AvailableHeat, InHeat);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetHeatPercentage);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetHeatAmount);
}

float UMVVM_ShipAttributes::GetMaxHeat() const
{
	return MaxHeat;
}

void UMVVM_ShipAttributes::SetMaxHeat(const float InMaxHeat)
{
	UE_MVVM_SET_PROPERTY_VALUE(MaxHeat, InMaxHeat);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetHeatPercentage);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetHeatAmount);
}

float UMVVM_ShipAttributes::GetHealthPercentage() const
{
	return UKismetMathLibrary::SafeDivide(Health, MaxHealth);
}

float UMVVM_ShipAttributes::GetEnergyPercentage() const
{
	return UKismetMathLibrary::SafeDivide(Energy, MaxEnergy);
}

float UMVVM_ShipAttributes::GetHeatPercentage() const
{
	return UKismetMathLibrary::SafeDivide(MaxHeat - AvailableHeat, MaxHeat);
}

float UMVVM_ShipAttributes::GetHeatAmount() const
{
	return MaxHeat - AvailableHeat;
}


void UMVVM_ShipAttributes::OnAttributeChanged(
	const FGameplayAttribute& Attribute,
	const FGameplayTag& AttributeTag,
	const float NewValue
)
{
	if (TagToAttributeSetterMap.Contains(AttributeTag))
	{
		TagToAttributeSetterMap[AttributeTag](NewValue);
	}
}

void UMVVM_ShipAttributes::OnReceivedDamage(const float DamageAmount, const bool bFatal)
{
	if (bFatal)
	{
		// TODO - do we need to do anything to the view to trigger death?
	}
}

void UMVVM_ShipAttributes::AddTagToAttributeSetterMap(
	const FGameplayTag& Tag,
	TFunction<void(UMVVM_ShipAttributes*, const float)> Setter
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

void UMVVM_ShipAttributes::InitializeValues(const ABlackbirdShip* Owner, const UBlackbirdAttributeSet* AttributeSet)
{
	SetMaxHealth(AttributeSet->GetMaxHealth());
	SetHealth(AttributeSet->GetHealth());
	SetMaxEnergy(AttributeSet->GetMaxEnergy());
	SetEnergy(AttributeSet->GetEnergy());
	SetMaxHeat(AttributeSet->GetMaxHeat());
	SetAvailableHeat(AttributeSet->GetAvailableHeat());
}
