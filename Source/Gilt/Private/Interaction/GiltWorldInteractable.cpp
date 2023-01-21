// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/GiltWorldInteractable.h"

#include "Components/BoxComponent.h"


AGiltWorldInteractable::AGiltWorldInteractable()
{
	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	RootComponent = Collision;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);
}

void AGiltWorldInteractable::GatherInteractionOptions(const FGiltInteractionQuery& InteractQuery,
	FInteractionOptionBuilder& OptionBuilder)
{
	OptionBuilder.AddInteractionOption(Option);
}

void AGiltWorldInteractable::HighlightInteractableActor()
{
	if (bIsHighlighted)
	{
		// TODO Turn Off Highlight
	}
	else
	{
		// TODO Turn On Highlight
	}
}
