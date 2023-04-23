// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/GiltGameState.h"

#include "AbilitySystem/GiltAbilitySystemComponent.h"
#include "GameModes/GiltExperienceManagerComponent.h"


AGiltGameState::AGiltGameState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AbilitySystemComponent = ObjectInitializer.CreateDefaultSubobject<UGiltAbilitySystemComponent>(this, TEXT("AbilitySystemComponent"));
	ExperienceManagerComponent = CreateDefaultSubobject<UGiltExperienceManagerComponent>("ExperienceManagerComponent");
}

void AGiltGameState::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	check(AbilitySystemComponent);
	AbilitySystemComponent->InitAbilityActorInfo(/*Owner=*/ this, /*Avatar=*/ this);
}

UAbilitySystemComponent* AGiltGameState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
