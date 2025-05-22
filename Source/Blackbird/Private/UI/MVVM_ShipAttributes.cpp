// Copyright Alien Shores 2025


#include "UI/MVVM_ShipAttributes.h"

#include "AbilitySystem/Attribute/BlackbirdAttributeSet.h"
#include "AbilitySystem/Attribute/BlackbirdAttributeTags.h"
#include "Ship/BlackbirdShip.h"

UMVVM_ShipAttributes::UMVVM_ShipAttributes()
{
	const FBlackbirdAttributeTags& AttributeTags = FBlackbirdAttributeTags::Get();
	AddTagToAttributeSetterMap(AttributeTags.Attributes_Primary_MaxHealth, &UMVVM_ShipAttributes::SetMaxHealth);
	AddTagToAttributeSetterMap(AttributeTags.Attributes_Primary_MaxEnergy, &UMVVM_ShipAttributes::SetMaxEnergy);
	AddTagToAttributeSetterMap(AttributeTags.Attributes_Primary_MaxHeat, &UMVVM_ShipAttributes::SetMaxHeat);
	AddTagToAttributeSetterMap(AttributeTags.Attributes_Vital_Health, &UMVVM_ShipAttributes::SetHealth);
	AddTagToAttributeSetterMap(AttributeTags.Attributes_Vital_Energy, &UMVVM_ShipAttributes::SetEnergy);
	AddTagToAttributeSetterMap(AttributeTags.Attributes_Vital_Heat, &UMVVM_ShipAttributes::SetHeat);
}

void UMVVM_ShipAttributes::BindDependencies(const ABlackbirdShip* Owner)
{
	if (IsValid(Owner))
	{
		if (UBlackbirdAttributeSet* AttributeSet = Owner->GetBlackbirdAttributeSet())
		{
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
}

float UMVVM_ShipAttributes::GetMaxHealth() const
{
	return MaxHealth;
}

void UMVVM_ShipAttributes::SetMaxHealth(const float InMaxHealth)
{
	UE_MVVM_SET_PROPERTY_VALUE(MaxHealth, InMaxHealth);
}

float UMVVM_ShipAttributes::GetEnergy() const
{
	return Energy;
}

void UMVVM_ShipAttributes::SetEnergy(const float InEnergy)
{
	UE_MVVM_SET_PROPERTY_VALUE(Energy, InEnergy);
}

float UMVVM_ShipAttributes::GetMaxEnergy() const
{
	return MaxEnergy;
}

void UMVVM_ShipAttributes::SetMaxEnergy(const float InMaxEnergy)
{
	UE_MVVM_SET_PROPERTY_VALUE(MaxEnergy, InMaxEnergy);
}

float UMVVM_ShipAttributes::GetHeat() const
{
	return Heat;
}

void UMVVM_ShipAttributes::SetHeat(const float InHeat)
{
	UE_MVVM_SET_PROPERTY_VALUE(Heat, InHeat);
}

float UMVVM_ShipAttributes::GetMaxHeat() const
{
	return MaxHeat;
}

void UMVVM_ShipAttributes::SetMaxHeat(const float InMaxHeat)
{
	UE_MVVM_SET_PROPERTY_VALUE(MaxHeat, InMaxHeat);
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
	SetHeat(AttributeSet->GetHeat());
}
