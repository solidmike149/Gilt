// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "GiltAIAbilitiesComponent.generated.h"

class UGiltAIAbilitiesData;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent, DisplayName="AI Abilities Component"))
class GILT_API UGiltAIAbilitiesComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	UGiltAIAbilitiesComponent();

	UFUNCTION(BlueprintCallable)
	bool EvaluateAndSelectAbility(float Distance, FGameplayTag& AbilityTag);

	UFUNCTION(BlueprintCallable)
	void NotifyAbilityExecution(FGameplayTag AbilityTag);

	//TODO Set AbilitiesDataClass Function

protected:
	
	TSubclassOf<UGiltAIAbilitiesData> AbilitiesDataClass;

	UPROPERTY(Transient)
	UGiltAIAbilitiesData* AbilitiesData;

	UPROPERTY(BlueprintReadWrite, Category = "Attacks")
	bool bIsInCombo;
};
