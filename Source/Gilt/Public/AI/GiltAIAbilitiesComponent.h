// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GiltAIAbilitiesTypes.h"
#include "Components/ActorComponent.h"
#include "GiltAIAbilitiesComponent.generated.h"

class UGiltAIAbilitiesData;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent, DisplayName="AI Abilities Component"))
class GILT_API UGiltAIAbilitiesComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	UGiltAIAbilitiesComponent();

	UFUNCTION(BlueprintPure, Category = "Gilt|AI")
	static UGiltAIAbilitiesComponent* FindAIAbilitiesComponent(const AActor* Actor) { return (Actor ? Actor->FindComponentByClass<UGiltAIAbilitiesComponent>() : nullptr); }

	virtual void BeginPlay() override;

	void SetAbilitiesData(UGiltAIAbilitiesData* NewAbilitiesData);

	UFUNCTION(BlueprintCallable)
	bool EvaluateAndSelectAbility(float Distance, FGameplayTag& OutAbilityTag);

	UFUNCTION(BlueprintCallable)
	void NotifyAbilityExecution(FGameplayTag AbilityTag, float Distance);

	UFUNCTION(BlueprintCallable)
	void DebugAbilityScores();

protected:

	UPROPERTY(EditDefaultsOnly)
	UGiltAIAbilitiesData* AbilitiesData;

	UPROPERTY(Transient)
	TMap<FGameplayTag, FAbility> Abilities;

	UPROPERTY(Transient)
	float ComboWindow;

	UPROPERTY(BlueprintReadWrite)
	bool bIsInCombo;
};
