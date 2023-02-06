// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GiltAIAbilitiesTypes.h"
#include "Engine/DataAsset.h"

#include "GiltAIAbilitiesData.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, Const)
class GILT_API UGiltAIAbilitiesData : public UDataAsset
{
	GENERATED_BODY()

public:

	UGiltAIAbilitiesData();

	UPROPERTY(EditAnywhere)
	TMap<FGameplayTag, FAbility> Abilities;

	UPROPERTY(EditAnywhere)
	float ComboWindow;
};
