// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/GiltGameplayAbility_Target.h"

#include "GiltLogChannels.h"
#include "AbilityTask/AbilityTask_PerformTargeting.h"
#include "Player/GiltPlayerController.h"
#include "UI/IndicatorSystem/IndicatorDescriptor.h"
#include "UI/IndicatorSystem/GiltIndicatorManagerComponent.h"

UGiltGameplayAbility_Target::UGiltGameplayAbility_Target(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ActivationPolicy = EGiltAbilityActivationPolicy::OnInputTriggered;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
}

void UGiltGameplayAbility_Target::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UGiltGameplayAbility_Target::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if (AGiltPlayerController* PC = GetGiltPlayerControllerFromActorInfo())
	{
		if (UGiltIndicatorManagerComponent* IndicatorManager = UGiltIndicatorManagerComponent::GetComponent(PC))
		{
			IndicatorManager->RemoveIndicator(CurrentIndicator);
		}
		else
		{
			UE_LOG(LogGilt, Warning, TEXT("The Indicator Component Manager is missing from this player controller"))
		}
	}
}

AActor* UGiltGameplayAbility_Target::GetFirstTarget(FTargetingRequestHandle RequestHandle)
{
	if (RequestHandle.IsValid())
	{
		if (FTargetingDefaultResultsSet* ResultData = FTargetingDefaultResultsSet::Find(RequestHandle))
		{
			if (ResultData && ResultData->TargetResults.IsEmpty())
			{
				return nullptr;
			}
			float FirstScore = ResultData->TargetResults[0].Score;
			float LastScore = ResultData->TargetResults.Last().Score;
			float Start = GetAvatarActorFromActorInfo()->GetActorForwardVector().Rotation().Yaw;
			if (FMath::Abs(Start - FirstScore) < FMath::Abs(Start - LastScore))
			{
				CurrentTarget = ResultData->TargetResults[0].HitResult.GetActor();
			}
			else
			{
				CurrentTarget = ResultData->TargetResults.Last().HitResult.GetActor();
			}

			SetIndicator(CurrentTarget);
			return CurrentTarget;
		}
	}
	return nullptr;
}

void UGiltGameplayAbility_Target::SetIndicator(AActor* TargetActor)
{
	if (AGiltPlayerController* PC = GetGiltPlayerControllerFromActorInfo())
	{
		if (UGiltIndicatorManagerComponent* IndicatorManager = UGiltIndicatorManagerComponent::GetComponent(PC))
		{
			
			IndicatorManager->RemoveIndicator(CurrentIndicator);
			
			UIndicatorDescriptor* Indicator = NewObject<UIndicatorDescriptor>();
			Indicator->SetDataObject(TargetActor);
			Indicator->SetSceneComponent(TargetActor->GetRootComponent());
			Indicator->SetIndicatorClass(DefaultTargetingWidgetClass);
			IndicatorManager->AddIndicator(Indicator);

			CurrentIndicator = Indicator;
		}
		else
		{
			UE_LOG(LogGilt, Warning, TEXT("The Indicator Component Manager is missing from this player controller"))
		}
	}
}
