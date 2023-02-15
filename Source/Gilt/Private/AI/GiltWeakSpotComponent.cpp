// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/GiltWeakSpotComponent.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"

UGiltWeakSpotComponent::UGiltWeakSpotComponent()
{
	bIsOpen = false;
}

void UGiltWeakSpotComponent::BeginPlay()
{
	Super::BeginPlay();

	UAbilitySystemComponent* AbilitySystemComponent = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwner());
	
	AbilitySystemComponent->GenericGameplayEventCallbacks.FindOrAdd(EventTag).AddUObject(this, &UGiltWeakSpotComponent::GameplayEventCallback);
}

void UGiltWeakSpotComponent::GameplayEventCallback(const FGameplayEventData* Payload)
{
	FGameplayEventData TempPayload = *Payload;
	TempPayload.EventTag = EventTag;
	if (!bIsOpen)
	{
		SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		bIsOpen = true;
	}
	else
	{
		SetCollisionEnabled(ECollisionEnabled::NoCollision);
		bIsOpen = false;
	}
	OnStatusChanged.Broadcast(bIsOpen, MoveTemp(TempPayload));
}
