// Copyright (c) Proud Turkeys

#pragma once

#include "CoreMinimal.h"
#include "AbomGameplayAbility_Action.h"
#include "AbomGameplayAbility_SideKick.generated.h"

/**
 *
 */
UCLASS()
class ABOMIRACERS_API UAbomGameplayAbility_SideKick : public UAbomGameplayAbility_Action
{
	GENERATED_BODY()

private:

	UFUNCTION(BlueprintCallable,  meta = (AllowPrivateAccess = "true"))
	FActiveGameplayEffectHandle ApplyGameplayEffect(TSubclassOf<UGameplayEffect> GE_ToApply, UAbilitySystemComponent* TargetASC,float Duration, bool bHasDuration = true);

	UFUNCTION(BlueprintCallable,  meta = (AllowPrivateAccess = "true"))
	bool CheckLimbPosition();
};
