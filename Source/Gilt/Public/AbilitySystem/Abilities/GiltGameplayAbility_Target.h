// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GiltGameplayAbility.h"
#include "Types/TargetingSystemTypes.h"
#include "GiltGameplayAbility_Target.generated.h"

class UIndicatorDescriptor;

/**
 * UGiltGameplayAbility_Target
 *
 * Gameplay ability used for targeting
 */
UCLASS(Abstract)
class GILT_API UGiltGameplayAbility_Target : public UGiltGameplayAbility
{
	GENERATED_BODY()

public:
	
	UGiltGameplayAbility_Target(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	UFUNCTION(BlueprintCallable)
	AActor* GetFirstTarget(FTargetingRequestHandle RequestHandle);

	UFUNCTION(BlueprintCallable)
	void SetIndicator(AActor* TargetActor);
	
protected:

	UPROPERTY(Transient, BlueprintReadWrite)
	AActor* CurrentTarget;

	UPROPERTY()
	UIndicatorDescriptor* CurrentIndicator;

	UPROPERTY(EditDefaultsOnly)
	UTargetingPreset* DefaultPreset;
	
	UPROPERTY(EditDefaultsOnly)
	TSoftClassPtr<UUserWidget> DefaultTargetingWidgetClass;
};
