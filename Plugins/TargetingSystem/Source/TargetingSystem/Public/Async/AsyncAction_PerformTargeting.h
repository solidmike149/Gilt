// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Types/TargetingSystemTypes.h"

#include "AsyncAction_PerformTargeting.generated.h"

class UTargetingPreset;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPerformTargetingReady, FTargetingRequestHandle, TargetingHandle);

/**
*	@class UAsyncAction_PerformTargeting
*/
UCLASS()
class UAsyncAction_PerformTargeting : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UAsyncAction_PerformTargeting(const FObjectInitializer& ObjectInitializer);

	virtual void Activate() override;
	
	UFUNCTION(BlueprintCallable, meta = (DefaultToSelf = "SourceActor", BlueprintInternalUseOnly = "true", DisplayName = "Perform Targeting Async Action"))
	static UAsyncAction_PerformTargeting* PerformTargetingRequest(AActor* SourceActor, UTargetingPreset* TargetingPreset, bool bUseAsyncTargeting);

	UFUNCTION(BlueprintCallable, meta = (DefaultToSelf = "SourceActor", BlueprintInternalUseOnly = "true", DisplayName = "Perform Filtering Async Action"))
	static UAsyncAction_PerformTargeting* PerformFilteringRequest(AActor* SourceActor, UTargetingPreset* TargetingPreset, bool bUseAsyncTargeting, const TArray<AActor*> InTargets);
	
	UPROPERTY(BlueprintAssignable)
	FPerformTargetingReady Targeted;

private:
	/** Method to seed the targeting request w/ the initial set of targets */
	void SetupInitialTargetsForRequest(const FTargetingRequestHandle& TargetingHandle) const;
	
	/** The targeting preset to use for targeting */
	UPROPERTY()
	TObjectPtr<UTargetingPreset> TargetingPreset = nullptr;

	/** The actor this task is running for */
	UPROPERTY()
	TWeakObjectPtr<AActor> WeakSourceActor;

	/** A set of targets to pre-seed the targeting request with (great for filtering targets without the needs for selection) */
	UPROPERTY()
	TArray<TObjectPtr<AActor>> InitialTargets;

	/** Flag to indicate we should be using async targeting (default is immediate execution) */
	UPROPERTY()
	uint8 bUseAsyncTargeting : 1;
};