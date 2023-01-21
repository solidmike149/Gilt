// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TargetingTasks.h"
#include "TargetingFilterTask_SortByDeltaRotation.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TARGETINGSYSTEM_API UTargetingFilterTask_SortByDeltaRotation : public UTargetingTask
{
	GENERATED_BODY()

public:
	UTargetingFilterTask_SortByDeltaRotation(const FObjectInitializer& ObjectInitializer);

	/** Evaluation function called by derived classes to process the targeting request */
	virtual void Execute(const FTargetingRequestHandle& TargetingHandle) const override;

protected:
	UPROPERTY(EditAnywhere, Category = "Target Sorting | Data")
	uint8 bAscending : 1;
	
	/** Debug Helper Methods */
	#if ENABLE_DRAW_DEBUG
private:
	virtual void DrawDebug(UTargetingSubsystem* TargetingSubsystem, FTargetingDebugInfo& Info, const FTargetingRequestHandle& TargetingHandle, float XOffset, float YOffset, int32 MinTextRowsToAdvance) const override;
	void BuildPreSortDebugString(const FTargetingRequestHandle& TargetingHandle, const TArray<FTargetingDefaultResultData>& TargetResults) const;
	void BuildPostSortDebugString(const FTargetingRequestHandle& TargetingHandle, const TArray<FTargetingDefaultResultData>& TargetResults) const;
	void ResetSortDebugStrings(const FTargetingRequestHandle& TargetingHandle) const;
#endif // ENABLE_DRAW_DEBUG
	/** ~Debug Helper Methods */
};
