// Copyright (c) Proud Turkeys


#include "AbilitySystem/Abilities/AbomGameplayAbility_SideKick.h"

#include "AbilitySystemLog.h"

FActiveGameplayEffectHandle UAbomGameplayAbility_SideKick::ApplyGameplayEffect(TSubclassOf<UGameplayEffect> GE_ToApply,
                                                                               UAbilitySystemComponent* TargetASC, float Duration, bool bHasDuration)
{
	ensure(GE_ToApply);

	FGameplayEffectContextHandle EffectContext = TargetASC->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	FGameplayEffectSpecHandle const SpecHandle = TargetASC->MakeOutgoingSpec(
		GE_ToApply, 1, EffectContext);

	ensure(SpecHandle.IsValid());

	if(bHasDuration)
	{
		SpecHandle.Data.Get()->SetDuration(Duration, true);
	}

	return TargetASC->ApplyGameplayEffectSpecToSelf(
		*SpecHandle.Data.Get());
}

bool UAbomGameplayAbility_SideKick::CheckLimbPosition()
{
	if (!OwnerLimb.Get())
	{
		ABILITY_LOG(Error, TEXT("Source object is not of type AAbomBodyPart_Limb."));
		CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
	}

	if(OwnerLimb->IsRight())
	{
		return true;
	}

	return false;
}

