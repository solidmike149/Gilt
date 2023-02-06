// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/GiltWorldInteractable.h"

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
		//Mesh->SetOverlayMaterial();
	}
	else
	{
		// TODO Turn On Highlight
		//Mesh->SetOverlayMaterial()
	}
}
