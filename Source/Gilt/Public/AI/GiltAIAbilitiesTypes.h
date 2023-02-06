// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "InstancedStruct.h"
#include "GiltAIAbilitiesTypes.generated.h"


USTRUCT(BlueprintType)
struct GILT_API FPostExecutionChange
{
	GENERATED_BODY()
	
	virtual ~FPostExecutionChange()
	{
	}

	UPROPERTY(EditAnywhere)
	FGameplayTag AbilityTag;
	
	virtual float GetScore(FGameplayTag& OutAbilityTag, float Distance) const;
};

USTRUCT(BlueprintType)
struct GILT_API FPostExecutionChange_BaseScore : public FPostExecutionChange
{
	GENERATED_BODY()

	FPostExecutionChange_BaseScore()
	{
		ModifyScore = 0.0f;
	}

	UPROPERTY(EditAnywhere)
	float ModifyScore;

	virtual float GetScore(FGameplayTag& OutAbilityTag, float Distance) const override;
};

USTRUCT(BlueprintType)
struct GILT_API FPostExecutionChange_Distance : public FPostExecutionChange
{
	GENERATED_BODY()

	FPostExecutionChange_Distance()
	{
		DistanceThreshold = 0.0f;
		ModifyScoreInThreshold = 0.0f;
		ModifyScoreOutThreshold = 0.0f;
	}

	UPROPERTY(EditAnywhere)
	float DistanceThreshold;

	UPROPERTY(EditAnywhere)
	float ModifyScoreInThreshold;

	UPROPERTY(EditAnywhere)
	float ModifyScoreOutThreshold;

	virtual float GetScore(FGameplayTag& OutAbilityTag, float Distance) const override;
};

USTRUCT(BlueprintType)
struct GILT_API FAbility
{
	GENERATED_BODY()

	FAbility()
	{
		Score = 0.0f;
		ScoreThreshold = 0.0f;
	}

	bool IsInThreshold() const
	{
		if (Score <= ScoreThreshold)
		{
			return true;
		}
		return false;
	}

	void IncrementScoreByCurve(float Distance)
	{
		if (DistanceCurve.GetRichCurveConst() && DistanceCurve.GetRichCurveConst()->GetNumKeys() > 0)
		{
			float AddingScore = DistanceCurve.GetRichCurveConst()->Eval(Distance);

			Score += AddingScore;
		
			Score = FMath::Clamp(Score, 0.0f, 1.0f);
		}
	}

	void SetScore(float ScoreModify)
	{
		float NewScore = Score + ScoreModify;
		NewScore = FMath::Clamp(NewScore, 0.0f, 1.0f);
		Score = NewScore;
	}

	UPROPERTY(EditAnywhere)
	FRuntimeFloatCurve DistanceCurve;

	UPROPERTY(EditAnywhere, meta=(ClampMin = 0.0f, ClampMax = 1.0f))
	float Score;

	UPROPERTY(EditAnywhere, meta=(ClampMin = 0.0f, ClampMax = 1.0f))
	float ScoreThreshold;

	UPROPERTY(EditAnywhere, meta = (BaseStruct = "/Script/Gilt.PostExecutionChange", ExcludeBaseStruct))
	TArray<FInstancedStruct> AbilityScoreChanges;
};
