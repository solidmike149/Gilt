// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "GiltEffectsData.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class GILT_API UGiltEffectsData : public UDataAsset
{
	GENERATED_BODY()

public:
	
	UGiltEffectsData();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<FGameplayTag, UTexture2D*> EffectsMap;

	UFUNCTION(BlueprintCallable)
	UTexture2D* GetImageForEffect(FGameplayTag EffectTag);
};
