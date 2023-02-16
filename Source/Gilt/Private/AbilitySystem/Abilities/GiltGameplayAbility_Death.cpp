// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/GiltGameplayAbility_Death.h"

#include "GameplayTagsManager.h"
#include "GiltGameplayTags.h"
#include "GiltLogChannels.h"
#include "AbilitySystem/GiltAbilitySystemComponent.h"

UGiltGameplayAbility_Death::UGiltGameplayAbility_Death(const FObjectInitializer& ObjectInitializer)
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerInitiated;

	UGameplayTagsManager::Get().CallOrRegister_OnDoneAddingNativeTagsDelegate(FSimpleDelegate::CreateUObject(this, &ThisClass::DoneAddingNativeTags));
}

void UGiltGameplayAbility_Death::DoneAddingNativeTags()
{
	if (HasAnyFlags(RF_ClassDefaultObject))
	{
		// Add the ability trigger tag as default to the CDO.
		FAbilityTriggerData TriggerData;
		TriggerData.TriggerTag = FGiltGameplayTags::Get().GameplayEvent_Death;
		TriggerData.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;
		AbilityTriggers.Add(TriggerData);
	}
}

void UGiltGameplayAbility_Death::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	check(ActorInfo);

	UGiltAbilitySystemComponent* GiltASC = CastChecked<UGiltAbilitySystemComponent>(ActorInfo->AbilitySystemComponent.Get());

	FGameplayTagContainer AbilityTypesToIgnore;
	AbilityTypesToIgnore.AddTag(FGiltGameplayTags::Get().Ability_Behavior_SurvivesDeath);

	// Cancel all abilities and block others from starting.
	GiltASC->CancelAbilities(nullptr, &AbilityTypesToIgnore, this);

	SetCanBeCanceled(false);

	if (!ChangeActivationGroup(EGiltAbilityActivationGroup::Exclusive_Blocking))
	{
		UE_LOG(LogGiltAbilitySystem, Error, TEXT("UGiltGameplayAbility_Death::ActivateAbility: Ability [%s] failed to change activation group to blocking."), *GetName());
	}

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UGiltGameplayAbility_Death::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	
}
