// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/GiltAIAbilitiesComponent.h"

#include "AI/GiltAIAbilitiesData.h"



UGiltAIAbilitiesComponent::UGiltAIAbilitiesComponent()
{
}

void UGiltAIAbilitiesComponent::BeginPlay()
{
	Super::BeginPlay();

	Abilities = AbilitiesData->Abilities;

	ComboWindow = AbilitiesData->ComboWindow;
}

bool UGiltAIAbilitiesComponent::EvaluateAndSelectAbility(float Distance, FGameplayTag& OutAbilityTag)
{
	TMap<FGameplayTag, FAbility> AbilitiesInThreshold;

	for (TTuple<FGameplayTag, FAbility>& Element : Abilities)
	{
		Element.Value.IncrementScoreByCurve(Distance);

		if (Element.Value.IsInThreshold())
		{
			AbilitiesInThreshold.Add(Element);
		}
	}
	switch (AbilitiesInThreshold.Num())
	{
	case 0:
		return false;
		
	case 1:
		OutAbilityTag = AbilitiesInThreshold.Array()[0].Key;
		return true;
		
	default:
		int32 LastIndex = AbilitiesInThreshold.Array().Num() - 1;
		OutAbilityTag = AbilitiesInThreshold.Array()[FMath::RandRange(0, LastIndex)].Key;
		return true;
	}
}

void UGiltAIAbilitiesComponent::NotifyAbilityExecution(FGameplayTag AbilityTag, float Distance)
{
	TArray<FInstancedStruct> ScoreChanges = Abilities.Find(AbilityTag)->AbilityScoreChanges;

	for (FInstancedStruct ScoreChange : ScoreChanges)
	{
		FGameplayTag AbilityToModify;
		float ModifyingScore = ScoreChange.Get<FPostExecutionChange>().GetScore(AbilityToModify, Distance);
		Abilities.Find(AbilityToModify)->SetScore(ModifyingScore);
	}

	bIsInCombo = true;
	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, FTimerDelegate::CreateLambda([this] { bIsInCombo = false; }), ComboWindow, false);
}
