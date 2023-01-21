// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "GiltBTService_SortMovesByDistance.generated.h"

/**
 * 
 */
UCLASS()
class GILT_API UGiltBTService_GetDistanceToPlayer : public UBTService
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector Distance;
	
	UPROPERTY(EditAnywhere, Category = "AI")
	bool ActivateDebug;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

public:
	
	UGiltBTService_GetDistanceToPlayer();
};
