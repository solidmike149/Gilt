// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "IndicatorLibrary.generated.h"

class UGiltIndicatorManagerComponent;

/**
 * 
 */
UCLASS()
class GILT_API UIndicatorLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UIndicatorLibrary();
	
	UFUNCTION(BlueprintCallable, Category = Indicator)
	static UGiltIndicatorManagerComponent* GetIndicatorManagerComponent(AController* Controller);
};

