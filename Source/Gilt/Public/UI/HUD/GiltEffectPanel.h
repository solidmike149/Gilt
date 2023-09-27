// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GameplayTagContainer.h"
#include "UI/GiltActivatableWidget.h"
#include "GiltEffectPanel.generated.h"


class UHorizontalBox;
class UGiltEffectSlot;
class UAbilitySystemComponent;


/**
 * 
 */
UCLASS()
class GILT_API UGiltEffectPanel : public UGiltActivatableWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	FGameplayTagContainer RegisteredTags;

protected:

	UPROPERTY()
	TMap<FActiveGameplayEffectHandle, UGiltEffectSlot*> EffectWidgetMap;

	UPROPERTY()
	UAbilitySystemComponent* ASC;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGiltEffectSlot> EffectSlotClass;
	
	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

	void OnActiveGameplayEffectAddedCallback(UAbilitySystemComponent* Target, const FGameplayEffectSpec& SpecApplied, FActiveGameplayEffectHandle ActiveHandle);
	void OnRemoveGameplayEffectCallback(const FActiveGameplayEffect& EffectRemoved);

	void GameplayEffectStackChanged(FActiveGameplayEffectHandle EffectHandle, int32 NewStackCount, int32 PreviousStackCount);

private:

	UPROPERTY(Meta = (BindWidget))
	UHorizontalBox* HorizontalBox;
};
