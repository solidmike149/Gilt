// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GiltGameplayTagLibrary.generated.h"

/**
 * 
 */
UCLASS()
class GILT_API UGiltGameplayTagLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UGiltGameplayTagLibrary();

	UFUNCTION(BlueprintPure, Category = GameplayTag)
	static FGameplayTagContainer FilterGameplayTagContainer(FGameplayTagContainer GameplayTagToFilter, FGameplayTagContainer FilterToApply);
};
