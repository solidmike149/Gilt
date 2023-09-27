// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectUIData.h"
#include "GiltGameplayEffectUIData.generated.h"

/**
 * 
 */
UCLASS()
class GILT_API UGiltGameplayEffectUIData : public UGameplayEffectUIData
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Data)
	UTexture* Image;
};
