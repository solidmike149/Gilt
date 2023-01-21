// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TargetingTasks.h"
#include "TargetingSelectionTask_DistanceFromSourceActor.generated.h"

/**
 * 
 */
UCLASS()
class TARGETINGSYSTEM_API UTargetingSelectionTask_DistanceFromSourceActor : public UTargetingTask
{
	GENERATED_BODY()

public:
	UTargetingSelectionTask_DistanceFromSourceActor(const FObjectInitializer& ObjectInitializer);

	/** Evaluation function called by derived classes to process the targeting request */
	virtual void Execute(const FTargetingRequestHandle& TargetingHandle) const override;

protected:
	
	UPROPERTY(EditAnywhere, Category = "Target Selection | Data")
	float Distance;

	UPROPERTY(EditAnywhere, Category = "Target Selection | Data")
	TEnumAsByte<ECollisionChannel> TargetingChannel;

	/** Debug Helper Methods */
	#if ENABLE_DRAW_DEBUG
private:
	virtual void DrawDebug(UTargetingSubsystem* TargetingSubsystem, FTargetingDebugInfo& Info, const FTargetingRequestHandle& TargetingHandle, float XOffset, float YOffset, int32 MinTextRowsToAdvance) const override;
	void AddSelectedActorsDebugString(const FTargetingRequestHandle& TargetingHandle, const AActor* SourceActor) const;
	void ResetSelectedActorsDebugString(const FTargetingRequestHandle& TargetingHandle) const;
#endif // ENABLE_DRAW_DEBUG
	/** ~Debug Helper Methods */
};
