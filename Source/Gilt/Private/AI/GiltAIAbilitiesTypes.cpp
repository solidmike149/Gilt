// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/GiltAIAbilitiesTypes.h"


float FPostExecutionChange::GetScore(FGameplayTag& OutAbilityTag, float Distance) const
{
	return 0.0f;
}

float FPostExecutionChange_BaseScore::GetScore(FGameplayTag& OutAbilityTag, float Distance) const
{
	OutAbilityTag = AbilityTag;
	return ModifyScore;
}

float FPostExecutionChange_Distance::GetScore(FGameplayTag& OutAbilityTag, float Distance) const
{
	OutAbilityTag = AbilityTag;
	if (Distance <= DistanceThreshold)
	{
		return ModifyScoreInThreshold;
	}
	return ModifyScoreOutThreshold;
}
