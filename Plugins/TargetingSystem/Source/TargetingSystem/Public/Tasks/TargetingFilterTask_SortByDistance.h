// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TargetingSortTask_Base.h"
#include "TargetingFilterTask_SortByDistance.generated.h"


/**
*	@class UTargetingFilterTask_SortByDistance
*
*	Simple sorting filter based on the distance to the source actor.
*	Note: This filter will use the FTargetingDefaultResultsSet and 
*	use the Score factor defined for each target to store the distance
*	and sort by that value.
*/
UCLASS(Blueprintable)
class UTargetingFilterTask_SortByDistance : public UTargetingSortTask_Base
{
	GENERATED_BODY()

protected:
	virtual float GetScoreForTarget(const FTargetingRequestHandle& TargetingHandle, const FTargetingDefaultResultData& TargetData) const override;

private:
	/** Returns the Source location, whether that comes from the source actor or the Source location in the Source Context */
	FVector GetSourceLocation(const FTargetingRequestHandle& TargetingHandle) const;
};