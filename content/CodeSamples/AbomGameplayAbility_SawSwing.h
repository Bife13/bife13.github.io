// Copyright (c) Proud Turkeys

#pragma once

#include "AbomGameplayAbility_Action.h"
#include "Abilities/Tasks/AbilityTask_ApplyRootMotionMoveToActorForce.h"
#include "Abilities/Tasks/AbilityTask_WaitDelay.h"
#include "AbilitySystem/AbomGameplayAbilityTargetActor_SphereTrace.h"
#include "AbilitySystem/Tasks/AsyncTaskWaitTargetDataUsingActor.h"
#include "BodyParts/AbomBodyPart_Limb_CusokThePooSaw.h"
#include "AbomGameplayAbility_SawSwing.generated.h"

/**
 * UAbomGameplayAbility_SawSwing
 *
 *	Gameplay ability used for The Saw Limb
 */
UCLASS()
class ABOMIRACERS_API UAbomGameplayAbility_SawSwing : public UAbomGameplayAbility_Action
{
	GENERATED_BODY()

public :

	UFUNCTION(BlueprintImplementableEvent)
	void ApplyStunCue();

	UFUNCTION(BlueprintImplementableEvent)
	void ApplyIdleCue();

	UFUNCTION(BlueprintImplementableEvent)
	void OnTargetFound();

protected:

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                             const FGameplayAbilityActivationInfo ActivationInfo,
	                             const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                        const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility,
	                        bool bWasCancelled) override;
private:

	UPROPERTY()
	TWeakObjectPtr<AAbomBodyPart_Limb_CusokThePooSaw> SawOwnerLimb;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Montages, meta = (AllowPrivateAccess = "true"), meta = (ClampMin = "0.0", ClampMax = "5.0", UIMin = "0.0", UIMax = "5.0"))
	float Montage_Antic_PlayRate = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Montages,	meta = (AllowPrivateAccess = "true"), meta = (ClampMin = "0.0", ClampMax = "5.0", UIMin = "0.0", UIMax = "5.0"))
	float Montage_Hit_PlayRate = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Montages,	meta = (AllowPrivateAccess = "true"))
	UAnimMontage* Montage_Idle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Montages,	meta = (AllowPrivateAccess = "true"))
	UAnimMontage* Montage_Antic;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Montages,	meta = (AllowPrivateAccess = "true"))
	UAnimMontage* Montage_Hit;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayEffects, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayEffect> GE_Antic;

	FActiveGameplayEffectHandle GE_AnticHandle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayEffects, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayEffect> GE_Idle;

	FActiveGameplayEffectHandle GE_IdleHandle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayEffects, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayEffect> GE_Hit;

	FActiveGameplayEffectHandle GE_HitHandle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayEffects, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayEffect> GE_BlockMovement;

	FActiveGameplayEffectHandle GE_BlockMovementCaster;

	FActiveGameplayEffectHandle GE_BlockMovementEnemy;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayEffects, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayEffect> GE_Knockback;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayEffects, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayEffect> GE_Stun;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayEffects, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayEffect> GE_Damage;

	UFUNCTION(Category = Trace)
	AAbomGameplayAbilityTargetActor_SphereTrace* GetSphereTraceTargetActor();

	UFUNCTION(Category = Trace)
	void LookForTarget();

	UFUNCTION(Category = Trace)
	void ConfigureTargetActor();

	UFUNCTION(Category = Trace)
	void OnValidTargetDataObtained(const FGameplayAbilityTargetDataHandle& Data);

	UFUNCTION()
	void TargetFound();

	FActiveGameplayEffectHandle ApplyGameplayEffect(TSubclassOf<UGameplayEffect> GE_ToApply, UAbilitySystemComponent* TargetASC, float Duration);
	FActiveGameplayEffectHandle ApplyGameplayEffect(TSubclassOf<UGameplayEffect> GE_ToApply, UAbilitySystemComponent* TargetASC);

	UPROPERTY()
	UAsyncTaskWaitTargetDataUsingActor* WaitTargetDataUsingActor;

	UPROPERTY()
	UAbilityTask_WaitDelay* WaitIdleDuration;

	UPROPERTY()
	AAbomGameplayAbilityTargetActor_SphereTrace* SphereTraceTargetActor;

	UPROPERTY()
	UAbilityTask_ApplyRootMotionMoveToActorForce* Snap;

	UPROPERTY()
	UAsyncTaskWaitTargetDataUsingActor* AsyncTaskWaitTargetDataUsingActor;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	AAbomCharacter* EnemyCharacter;

	//Duration of Idle Phase
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = IdlePhase, meta = (AllowPrivateAccess = "true"))
	float IdleDuration = 2.0f;

	// Max Range of Trace
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Trace, meta = (AllowPrivateAccess = "true"))
	float Trace_MaxRange = 100.0f;

	// Radius of the Trace
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Trace, meta = (AllowPrivateAccess = "true"))
	float Trace_SphereRadius = 75.0f;

	// Offset of the trace
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Trace, meta = (AllowPrivateAccess = "true"))
	float Trace_OffSet = 0;

	// Profile used for Trace collision
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Trace, meta = (AllowPrivateAccess = "true"))
	FName Trace_ProfileName = "IgnoreAllExceptPawn";

	// Duration of Hit Phase
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = HitPhase, meta = (AllowPrivateAccess = "true"))
	float HitDuration = 2.0f;

	// Duration of Snap
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Snap, meta = (AllowPrivateAccess = "true"))
	float SnapToEnemyDuration = 0.2f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Snap, meta = (AllowPrivateAccess = "true"))
	double MinDistanceNeededForSnap;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Snap,	meta = (AllowPrivateAccess = "true"))
	UCurveFloat* SawSnapStrengthCurve;

	FRotator SnapLookDirection;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Hit, meta = (AllowPrivateAccess = "true"))
	FName TargetSocketName = "spine_C0_spine_03_jnt";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Debugging, meta = (AllowPrivateAccess = "true"))
	bool bIsDebug = true;

	void RemoveTagsFromEnemy();

	UFUNCTION()
	void RemoveEnemyLimb();

	UFUNCTION()
	void OnAnticPhaseEnd();

	UFUNCTION()
	void OnIdlePhaseEnd();

	UFUNCTION()
    void StartAnticPhase();

	UFUNCTION()
	void OnSnapStateDurationEnded();

	UFUNCTION()
	void OnSnapFinished(bool DestinationReached, bool TimedOut, FVector FinalTargetLocation);

	UFUNCTION()
	void StartHeadpunchPhase();

	UFUNCTION()
	void OnHeadpunchPhaseEnd();

	UFUNCTION()
	void OnKnockBackNotify();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Headpunch, meta = (AllowPrivateAccess = "true"))
	float HeadpunchStunDuration = 2.0f;
};
