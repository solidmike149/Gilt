// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/GiltEffectPanel.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "ActiveGameplayEffectHandle.h"
#include "AbilitySystem/GiltGameplayEffectUIData.h"
#include "Components/HorizontalBox.h"
#include "UI/HUD/GiltEffectSlot.h"

void UGiltEffectPanel::NativeConstruct()
{
	Super::NativeConstruct();

	ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwningPlayerPawn());

	ASC->OnActiveGameplayEffectAddedDelegateToSelf.AddUObject(this, &UGiltEffectPanel::OnActiveGameplayEffectAddedCallback);
	ASC->OnAnyGameplayEffectRemovedDelegate().AddUObject(this, &UGiltEffectPanel::OnRemoveGameplayEffectCallback);
}

void UGiltEffectPanel::NativeDestruct()
{
	Super::NativeDestruct();

	ASC = nullptr;
}

void UGiltEffectPanel::OnActiveGameplayEffectAddedCallback(UAbilitySystemComponent* Target,
                                                           const FGameplayEffectSpec& SpecApplied,
                                                           FActiveGameplayEffectHandle ActiveHandle)
{
	FGameplayTagContainer AssetTags;
	SpecApplied.GetAllAssetTags(AssetTags);

	FGameplayTagContainer GrantedTags;
	SpecApplied.GetAllGrantedTags(GrantedTags);
	
	if (AssetTags.HasAny(RegisteredTags) || GrantedTags.HasAny(RegisteredTags))
	{
		UGiltEffectSlot* NewSlot = Cast<UGiltEffectSlot>(CreateWidget(this, EffectSlotClass));
		UTexture* Image = Cast<UGiltGameplayEffectUIData>(Target->GetGameplayEffectCDO(ActiveHandle)->UIData)->Image;
		NewSlot->SetupEffect(Image, SpecApplied.GetDuration());
		HorizontalBox->AddChildToHorizontalBox(NewSlot);
		EffectWidgetMap.Add(ActiveHandle, NewSlot);
		
		ASC->OnGameplayEffectStackChangeDelegate(ActiveHandle)->AddUObject(this, &UGiltEffectPanel::GameplayEffectStackChanged);
		GameplayEffectStackChanged(ActiveHandle, 1, 0);
	}
}

void UGiltEffectPanel::OnRemoveGameplayEffectCallback(const FActiveGameplayEffect& EffectRemoved)
{
	FGameplayTagContainer AssetTags;
	EffectRemoved.Spec.GetAllAssetTags(AssetTags);

	FGameplayTagContainer GrantedTags;
	EffectRemoved.Spec.GetAllGrantedTags(GrantedTags);

	if (AssetTags.HasAny(RegisteredTags) || GrantedTags.HasAny(RegisteredTags))
	{
		GameplayEffectStackChanged(EffectRemoved.Handle, 0, 1);

		UGiltEffectSlot* SlotToRemove = EffectWidgetMap.FindChecked(EffectRemoved.Handle);
	
		if(SlotToRemove)
		{
			SlotToRemove->RemoveFromParent();
		}
		EffectWidgetMap.Remove(EffectRemoved.Handle);
	}
}

void UGiltEffectPanel::GameplayEffectStackChanged(FActiveGameplayEffectHandle EffectHandle, int32 NewStackCount,
	int32 PreviousStackCount)
{
	UGiltEffectSlot* SlotToUpdate = EffectWidgetMap.FindChecked(EffectHandle);
	SlotToUpdate->UpdateEffectStack(NewStackCount, PreviousStackCount);
}
