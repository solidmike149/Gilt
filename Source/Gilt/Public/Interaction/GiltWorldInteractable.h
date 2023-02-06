// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GiltInteractableTargetInterface.h"
#include "Actors/GiltWorldActor.h"
#include "GiltWorldInteractable.generated.h"

class UBoxComponent;
UCLASS(Abstract, Blueprintable)
class GILT_API AGiltWorldInteractable : public AGiltWorldActor, public IGiltInteractableTargetInterface
{
	GENERATED_BODY()

public:

	virtual void GatherInteractionOptions(const FGiltInteractionQuery& InteractQuery, FInteractionOptionBuilder& OptionBuilder) override;

	virtual void HighlightInteractableActor() override;

protected:

	bool bIsHighlighted;
	
	UPROPERTY(EditAnywhere)
	FGiltInteractionOption Option;
};
