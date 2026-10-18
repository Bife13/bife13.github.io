// Copyright (c) Proud Turkeys

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AbomGameplayAbility_Action.h"
#include "AbilitySystem/AbomGameplayAbilityTargetActor_SphereTrace.h"
#include "AbomGameplayAbility_BigPunch.generated.h"

/**
 *
 */
UCLASS()
class ABOMIRACERS_API UAbomGameplayAbility_BigPunch : public UAbomGameplayAbility_Action
{
	GENERATED_BODY()

private :

	UFUNCTION(BlueprintCallable,  meta = (AllowPrivateAccess = "true"))
	FVector GetOwnerLimbPosition();

    UFUNCTION(BlueprintCallable,  meta = (AllowPrivateAccess = "true"))
	FActiveGameplayEffectHandle ApplyGameplayEffect(TSubclassOf<UGameplayEffect> GE_ToApply, UAbilitySystemComponent* TargetASC,float Duration, bool bHasDuration = true);

	UFUNCTION(Category = Trace)
	AAbomGameplayAbilityTargetActor_SphereTrace* GetSphereTraceTargetActor();

	UFUNCTION(Category = Trace,BlueprintCallable,  meta = (AllowPrivateAccess = "true"))
	void ConfigureTargetActor();

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	AAbomGameplayAbilityTargetActor_SphereTrace* SphereTraceTargetActor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Trace, meta = (AllowPrivateAccess = "true"))
	FName Trace_ProfileName = "IgnoreAllExceptPawn";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Debugging, meta = (AllowPrivateAccess = "true"))
	bool bIsDebug = true;

	// Max Range of Trace
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Trace, meta = (AllowPrivateAccess = "true"))
	float TraceOffSet;

	// Max Range of Trace
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Trace, meta = (AllowPrivateAccess = "true"))
	float Trace_MaxRange = 100.0f;

	// Radius of the Trace
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Trace, meta = (AllowPrivateAccess = "true"))
	float Trace_SphereRadius = 75.0f;

	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true"))
	TArray<AActor*> RemoveDuplicateActors(TArray<AActor*> ActorArray);

};
