// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/IndicatorSystem/IndicatorLibrary.h"

#include "UI/IndicatorSystem/GiltIndicatorManagerComponent.h"


UIndicatorLibrary::UIndicatorLibrary()
{
}

UGiltIndicatorManagerComponent* UIndicatorLibrary::GetIndicatorManagerComponent(AController* Controller)
{
	return UGiltIndicatorManagerComponent::GetComponent(Controller);
}
