// Copyright (c) Proud Turkeys

#include "AbilitySystem/Abilities/AbomGameplayAbility_SawSwing.h"
#include "AbilitySystemLog.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"

void UAbomGameplayAbility_SawSwing::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                    const FGameplayAbilityActorInfo* ActorInfo,
                                                    const FGameplayAbilityActivationInfo ActivationInfo,
                                                    const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		CancelAbility(Handle, ActorInfo, ActivationInfo, true);
	}

	//Check Source Limb to see if its correctly setup, if not, Cancel ability
	if (!OwnerLimb.Get())
	{
		ABILITY_LOG(Error, TEXT("Source object is not of type AAbomBodyPart_Limb."));
		CancelAbility(Handle, ActorInfo, ActivationInfo, true);
	}

	SawOwnerLimb = Cast<AAbomBodyPart_Limb_CusokThePooSaw>(OwnerLimb);

	StartAnticPhase();

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UAbomGameplayAbility_SawSwing::EndAbility(const FGameplayAbilitySpecHandle Handle,
                                               const FGameplayAbilityActorInfo* ActorInfo,
                                               const FGameplayAbilityActivationInfo ActivationInfo,
                                               bool bReplicateEndAbility, bool bWasCancelled)
{
	if (WaitTargetDataUsingActor)
	{
		WaitTargetDataUsingActor->EndTask();
	}

	if (GE_AnticHandle.IsValid())
	{
		GetAbilitySystemComponentFromActorInfo()->RemoveActiveGameplayEffect(GE_AnticHandle);
	}

	if (GE_IdleHandle.IsValid())
	{
		GetAbilitySystemComponentFromActorInfo()->RemoveActiveGameplayEffect(GE_IdleHandle);
	}

	if (GE_BlockMovementCaster.IsValid())
	{
		GetAbilitySystemComponentFromActorInfo()->RemoveActiveGameplayEffect(GE_BlockMovementCaster);
	}

	RemoveTagsFromEnemy();

	if(SawOwnerLimb.IsValid())
	{
		if(SawOwnerLimb->OnKnockBack.IsBound())
		{
			SawOwnerLimb->OnKnockBack.Clear();
		}
		if(SawOwnerLimb->OnTimelineEnd.IsBound())
		{
			SawOwnerLimb->OnTimelineEnd.Clear();
		}
	}

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

FActiveGameplayEffectHandle UAbomGameplayAbility_SawSwing::ApplyGameplayEffect(
	TSubclassOf<UGameplayEffect> GE_ToApply, UAbilitySystemComponent* TargetASC,
	float Duration)
{
	ensure(GE_ToApply);

	FGameplayEffectContextHandle EffectContext = TargetASC->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	FGameplayEffectSpecHandle const SpecHandle = TargetASC->MakeOutgoingSpec(
		GE_ToApply, 1, EffectContext);

	ensure(SpecHandle.IsValid());

	SpecHandle.Data.Get()->SetDuration(Duration, true);
	return TargetASC->ApplyGameplayEffectSpecToSelf(
		*SpecHandle.Data.Get());
}

FActiveGameplayEffectHandle UAbomGameplayAbility_SawSwing::ApplyGameplayEffect(TSubclassOf<UGameplayEffect> GE_ToApply,
	UAbilitySystemComponent* TargetASC)
{
	ensure(GE_ToApply);

	FGameplayEffectContextHandle EffectContext = TargetASC->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	FGameplayEffectSpecHandle const SpecHandle = TargetASC->MakeOutgoingSpec(
		GE_ToApply, 1, EffectContext);

	ensure(SpecHandle.IsValid());

	return TargetASC->ApplyGameplayEffectSpecToSelf(
		*SpecHandle.Data.Get());
}
