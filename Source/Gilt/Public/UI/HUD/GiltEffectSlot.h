// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GiltEffectSlot.generated.h"

/**
 * 
 */
UCLASS()
class GILT_API UGiltEffectSlot : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent)
	void SetupEffect(UTexture* Image, float Duration);
	
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateEffectStack(int32 NewStackCount, int32 PreviousStackCount);
};
