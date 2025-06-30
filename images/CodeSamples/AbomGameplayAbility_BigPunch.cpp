// Copyright (c) Proud Turkeys


#include "AbilitySystem/Abilities/AbomGameplayAbility_BigPunch.h"

FVector UAbomGameplayAbility_BigPunch::GetOwnerLimbPosition()
{
	if (OwnerLimb.IsValid())
	{
		return OwnerLimb->GetActorLocation();
	}

	return FVector::Zero();
}

FActiveGameplayEffectHandle UAbomGameplayAbility_BigPunch::ApplyGameplayEffect(TSubclassOf<UGameplayEffect> GE_ToApply,
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

AAbomGameplayAbilityTargetActor_SphereTrace* UAbomGameplayAbility_BigPunch::GetSphereTraceTargetActor()
{
	if (SphereTraceTargetActor)
	{
		return SphereTraceTargetActor;
	}
	SphereTraceTargetActor = GetWorld()->SpawnActor<AAbomGameplayAbilityTargetActor_SphereTrace>();
	SphereTraceTargetActor->SetOwner(GetAvatarActorFromActorInfo());
	SphereTraceTargetActor->SourceActor = GetAvatarActorFromActorInfo();
	return SphereTraceTargetActor;
}

void UAbomGameplayAbility_BigPunch::ConfigureTargetActor()
{
	// Setup TargetActor
	GetSphereTraceTargetActor();

	// Setup TargetActor Location
	FGameplayAbilityTargetingLocationInfo* LocationInfo = new FGameplayAbilityTargetingLocationInfo;
	LocationInfo->LocationType = EGameplayAbilityTargetingLocationType::LiteralTransform;
	FVector const ForwardVector = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	FVector const NewLocation = GetAvatarActorFromActorInfo()->GetActorLocation() + ForwardVector * TraceOffSet;
	LocationInfo->LiteralTransform = FTransform(ForwardVector.Rotation(), NewLocation);
	LocationInfo->SourceActor = GetAvatarActorFromActorInfo();

	// Setup TargetActor Collision profile
	FCollisionProfileName ProfileName;
	ProfileName.Name = Trace_ProfileName;

	// Setup TargetActor Collision filter
	TSharedPtr<FGameplayTargetDataFilter> TargetDataFilter(new FGameplayTargetDataFilter);
	TargetDataFilter->RequiredActorClass = GetAvatarActorFromActorInfo()->GetClass();
	TargetDataFilter->SelfActor = GetAvatarActorFromActorInfo();
	TargetDataFilter->SelfFilter = ETargetDataFilterSelf::TDFS_NoSelf;

	FGameplayTargetDataFilterHandle* DataFilterHandle = new FGameplayTargetDataFilterHandle;
	DataFilterHandle->Filter = TargetDataFilter;

	// Configure TargetActor
	SphereTraceTargetActor->Configure(*LocationInfo, ProfileName, *DataFilterHandle, true,
									  true, false, bIsDebug, false,
									  Trace_MaxRange, Trace_SphereRadius, 10);
}

TArray<AActor*> UAbomGameplayAbility_BigPunch::RemoveDuplicateActors(TArray<AActor*> ActorArray)
{
		TSet<FString> ActorNames;
		TArray<AActor*> UniqueActors;

		for (AActor* Actor : ActorArray)
		{
			if (Actor)
			{
				FString ActorName = Actor->GetName();

				if (!ActorNames.Contains(ActorName))
				{
					ActorNames.Add(ActorName);
					UniqueActors.Add(Actor);
				}
			}
		}
		return  UniqueActors;
}
