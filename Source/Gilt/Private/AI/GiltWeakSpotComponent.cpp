// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/GiltWeakSpotComponent.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"

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
	OnStatusChanged.Broadcast(bIsOpen, MoveTemp(TempPayload));
}
