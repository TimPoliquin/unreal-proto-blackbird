#pragma once

#include "GameplayTagContainer.h"
#include "AttributeSet.h"
#include "BlackbirdAttributeSetTypes.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

template <class T>
using TStaticFuncPtr = typename TBaseStaticDelegateInstance<T, FDefaultDelegateUserPolicy>::FFuncPtr;

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnReceivedDamageSignature, const float, DamageAmount, const bool, bFatal);

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(
	FOnAttributeChangedSignature,
	const FGameplayAttribute&,
	Attribute,
	const FGameplayTag&,
	AttributeTag,
	const float,
	NewValue
);
