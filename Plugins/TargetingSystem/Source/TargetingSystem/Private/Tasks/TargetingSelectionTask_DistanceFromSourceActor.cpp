// Fill out your copyright notice in the Description page of Project Settings.


#include "Tasks/TargetingSelectionTask_DistanceFromSourceActor.h"

#include "DrawDebugHelpers.h"

#if ENABLE_DRAW_DEBUG
#include "Engine/Canvas.h"
#endif // ENABLE_DRAW_DEBUG
#include "TargetingSystem/TargetingSubsystem.h"

UTargetingSelectionTask_DistanceFromSourceActor::UTargetingSelectionTask_DistanceFromSourceActor(
	const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}

void UTargetingSelectionTask_DistanceFromSourceActor::Execute(const FTargetingRequestHandle& TargetingHandle) const
{
	Super::Execute(TargetingHandle);

	SetTaskAsyncState(TargetingHandle, ETargetingTaskAsyncState::Executing);

#if ENABLE_DRAW_DEBUG
	ResetSelectedActorsDebugString(TargetingHandle);
#endif // ENABLE_DRAW_DEBUG

	if (TargetingHandle.IsValid())
	{
		if (const FTargetingSourceContext* SourceContext = FTargetingSourceContext::Find(TargetingHandle))
		{
			if (SourceContext->SourceActor)
			{
				FCollisionQueryParams Params;
				
				TArray<FOverlapResult> OverlapResults;
				FVector SourceActorLocation = SourceContext->SourceActor->GetActorLocation();
				UWorld* World = SourceContext->SourceActor->GetWorld();
				World->OverlapMultiByChannel(OUT OverlapResults, SourceActorLocation, FQuat::Identity, TargetingChannel, FCollisionShape::MakeSphere(Distance), Params);
				//DrawDebugSphere(World, SourceActorLocation, Distance, 32, FColor::Blue, false, 5, 0, 10);
				
				FTargetingDefaultResultsSet& Results = FTargetingDefaultResultsSet::FindOrAdd(TargetingHandle);

				if(Results.TargetResults.IsEmpty())
				{
					for (const FOverlapResult& OverlapResult : OverlapResults)
					{
						FTargetingDefaultResultData* NewResultData = new(Results.TargetResults) FTargetingDefaultResultData();
						NewResultData->HitResult.HitObjectHandle = FActorInstanceHandle(OverlapResult.GetActor());
						NewResultData->HitResult.Location = OverlapResult.GetActor()->GetActorLocation();
					}
				}
				else
				{
					TArray<AActor*> ActorsToAdd;
					
					for (const FTargetingDefaultResultData& ResultData : Results.TargetResults)
					{
						for (const FOverlapResult& OverlapResult : OverlapResults)
						{
							if (ResultData.HitResult.GetActor() == OverlapResult.GetActor())
							{
								break;
							}
							ActorsToAdd.AddUnique(OverlapResult.GetActor());
							
						}
					}

					for ( AActor* ActorToAdd : ActorsToAdd)
					{
						FTargetingDefaultResultData* NewResultData = new(Results.TargetResults) FTargetingDefaultResultData();
						NewResultData->HitResult.HitObjectHandle = FActorInstanceHandle(ActorToAdd);
						NewResultData->HitResult.Location = ActorToAdd->GetActorLocation();
					}
				}
			}
		}
	}

	SetTaskAsyncState(TargetingHandle, ETargetingTaskAsyncState::Completed);
}


#if ENABLE_DRAW_DEBUG

void UTargetingSelectionTask_DistanceFromSourceActor::DrawDebug(UTargetingSubsystem* TargetingSubsystem, FTargetingDebugInfo& Info, const FTargetingRequestHandle& TargetingHandle, float XOffset, float YOffset, int32 MinTextRowsToAdvance) const
{
#if WITH_EDITORONLY_DATA
	if (UTargetingSubsystem::IsTargetingDebugEnabled())
	{
		FTargetingDebugData& DebugData = FTargetingDebugData::FindOrAdd(TargetingHandle);
		FString& ScratchPadString = DebugData.DebugScratchPadStrings.FindOrAdd(GetNameSafe(this));
		if (!ScratchPadString.IsEmpty())
		{
			if (Info.Canvas)
			{
				Info.Canvas->SetDrawColor(FColor::Yellow);
			}

			FString TaskString = FString::Printf(TEXT(": %s"), *ScratchPadString);
			TargetingSubsystem->DebugLine(Info, TaskString, XOffset, YOffset, MinTextRowsToAdvance);
		}
	}
#endif // WITH_EDITORONLY_DATA
}

void UTargetingSelectionTask_DistanceFromSourceActor::AddSelectedActorsDebugString(const FTargetingRequestHandle& TargetingHandle, const AActor* SourceActor) const
{
#if WITH_EDITORONLY_DATA
	if (SourceActor && UTargetingSubsystem::IsTargetingDebugEnabled())
	{
		FTargetingDebugData& DebugData = FTargetingDebugData::FindOrAdd(TargetingHandle);
		FString& ScratchPadString = DebugData.DebugScratchPadStrings.FindOrAdd(GetNameSafe(this));

		ScratchPadString = FString::Printf(TEXT("%s"), *GetNameSafe(SourceActor));
	}
#endif // WITH_EDITORONLY_DATA
}

void UTargetingSelectionTask_DistanceFromSourceActor::ResetSelectedActorsDebugString(const FTargetingRequestHandle& TargetingHandle) const
{
#if WITH_EDITORONLY_DATA
	FTargetingDebugData& DebugData = FTargetingDebugData::FindOrAdd(TargetingHandle);
	FString& ScratchPadString = DebugData.DebugScratchPadStrings.FindOrAdd(GetNameSafe(this));
	ScratchPadString.Reset();
#endif // WITH_EDITORONLY_DATA
}

#endif // ENABLE_DRAW_DEBUG

