// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/GiltAIAbilitiesComponent.h"

#include "AI/GiltAIAbilitiesData.h"


// Sets default values for this component's properties
UGiltAIAbilitiesComponent::UGiltAIAbilitiesComponent()
{
}

bool UGiltAIAbilitiesComponent::EvaluateAndSelectAbility(float Distance, FGameplayTag& AbilityTag)
{
	TMap<FGameplayTag, FAbility>& Abilities = AbilitiesData->Abilities;

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
		AbilityTag = AbilitiesInThreshold.Array()[0].Key;
		return true;
		
	default:
		int32 LastIndex = AbilitiesInThreshold.Array().Num() - 1;
		AbilityTag = AbilitiesInThreshold.Array()[FMath::RandRange(0, LastIndex)].Key;
		return true;
	}
}

void UGiltAIAbilitiesComponent::NotifyAbilityExecution(FGameplayTag AbilityTag)
{
	/*FCombo ActiveCombo = AttackData[AttackIndex].ComboData;

	ATiAIControllerBase* AIController = Cast<ATiAIControllerBase>(GetOwner());

	if(AIController)
	{
		if (AIController->bIsInComboCpp)
		{
			int32 Index = 0;
			for (FAttack& Attack : AttackData)
			{
				if (Index == AttackIndex)
				{
					Attack.Score -= Attack.DecrementScoreExecuted;
				}
			
				else if (Index == ActiveCombo.Index)
				{
					Attack.Score += ActiveCombo.IncrementScore;
				}
			
				else
				{
					Attack.Score -= Attack.DecrementScoreBase;
				}

				Attack.Score = FMath::Clamp(Attack.Score, 0.0f, 1.0f);
				Index ++;
			}	
		}
	
		else
		{
			int32 Index = 0;
		
			for (FAttack& Attack : AttackData)
			{
				if (Index == AttackIndex)
				{
					Attack.Score -= Attack.DecrementScoreExecuted;
				}
			
				else if(Index == ActiveCombo.Index)
				{
					Attack.Score += ActiveCombo.IncrementScore;
				}
			
				Attack.Score = FMath::Clamp(Attack.Score, 0.0f, 1.0f);
				Index ++;
			}
		}	
	}*/
}
