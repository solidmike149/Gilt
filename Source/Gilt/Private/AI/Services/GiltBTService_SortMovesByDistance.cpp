// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/GiltBTService_SortMovesByDistance.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UGiltBTService_GetDistanceToPlayer::UGiltBTService_GetDistanceToPlayer()
{
	ActivateDebug = false;
}


void UGiltBTService_GetDistanceToPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (ensure(BlackboardComp))
	{
		AActor* TargetActor = Cast<AActor>(BlackboardComp->GetValueAsObject("Player"));
		if (TargetActor)
		{
			AAIController* MyController = OwnerComp.GetAIOwner();
			if (ensure(MyController))
			{
				APawn* AIPawn = MyController->GetPawn();
				if (ensure(AIPawn))
				{
					float DistanceTo = FVector::Distance(TargetActor->GetActorLocation(), AIPawn->GetActorLocation());

					BlackboardComp->SetValueAsFloat(Distance.SelectedKeyName, DistanceTo);
					
					if (ActivateDebug)
					{
						FString DistanceDebug = FString::Printf(TEXT("Distance: %f"), DistanceTo);
						GEngine->AddOnScreenDebugMessage(-1, Interval, FColor::Green, DistanceDebug);
					}
				}
			}
		}
	}
}
