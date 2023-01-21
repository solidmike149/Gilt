// Fill out your copyright notice in the Description page of Project Settings.


#include "Tasks/TargetingFilterTask_SortByDistance.h"


float UTargetingFilterTask_SortByDistance::GetScoreForTarget(const FTargetingRequestHandle& TargetingHandle, const FTargetingDefaultResultData& TargetData) const
{
	FVector SourceLocation = GetSourceLocation(TargetingHandle);
	if (AActor* TargetActor = TargetData.HitResult.GetActor())
	{
		FVector TargetLocation = TargetActor->GetActorLocation();
		return FVector::DistSquared(SourceLocation, TargetLocation);
	}
	return 0.f;
}

FVector UTargetingFilterTask_SortByDistance::GetSourceLocation(const FTargetingRequestHandle& TargetingHandle) const
{
	FVector SourceLocation = FVector::ZeroVector;
	if (FTargetingSourceContext* SourceContext = FTargetingSourceContext::Find(TargetingHandle))
	{
		if (SourceContext->SourceActor)
		{
			SourceLocation = SourceContext->SourceActor->GetActorLocation();
		}
		else if (!SourceContext->SourceLocation.IsZero())
		{
			SourceLocation = SourceContext->SourceLocation;
		}
	}

	return SourceLocation;
}