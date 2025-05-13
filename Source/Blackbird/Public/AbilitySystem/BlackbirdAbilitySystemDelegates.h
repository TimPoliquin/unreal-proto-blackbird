#pragma once

#include "CoreMinimal.h"
#include "BlackbirdAbilitySystemDelegates.generated.h"

class UBlackbirdAbilitySystemComponent;

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBlackbirdAbilitySystemReadySignature, UBlackbirdAbilitySystemComponent*, BlackbirdAbilitySystemComponent);
