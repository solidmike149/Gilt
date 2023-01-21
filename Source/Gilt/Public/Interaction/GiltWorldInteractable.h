// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GiltInteractableTargetInterface.h"
#include "GameFramework/Actor.h"
#include "GiltWorldInteractable.generated.h"

class UBoxComponent;
UCLASS(Abstract, Blueprintable)
class GILT_API AGiltWorldInteractable : public AActor, public IGiltInteractableTargetInterface
{
	GENERATED_BODY()

public:

	AGiltWorldInteractable();

	virtual void GatherInteractionOptions(const FGiltInteractionQuery& InteractQuery, FInteractionOptionBuilder& OptionBuilder) override;

	virtual void HighlightInteractableActor() override;

protected:

	bool bIsHighlighted;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* Collision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* Mesh;
	
	UPROPERTY(EditAnywhere)
	FGiltInteractionOption Option;
};
