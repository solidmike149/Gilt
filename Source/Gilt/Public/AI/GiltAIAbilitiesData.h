// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "InstancedStruct.h"
#include "UObject/Object.h"
#include "GiltAIAbilitiesData.generated.h"

USTRUCT(BlueprintType)
struct GILT_API FPostExecutionChange
{
	GENERATED_BODY()
	
	virtual ~FPostExecutionChange()
	{
	}

	UPROPERTY(EditAnywhere)
	FGameplayTag AbilityTag;
	
	virtual float GetScore(FGameplayTag& OutAbilityTag) const;
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

	//virtual float GetScore(FGameplayTag& AbilityTag) const override;
};

USTRUCT(BlueprintType)
struct GILT_API FPostExecutionChange_Distance : public FPostExecutionChange
{
	GENERATED_BODY()

	FPostExecutionChange_Distance()
	{
		ScoreMultiplier = 0.0f;
	}

	UPROPERTY(EditAnywhere)
	float ScoreMultiplier;

	//virtual float GetScore(FGameplayTag& AbilityTag) const override;
};

USTRUCT(BlueprintType)
struct GILT_API FAbility
{
	GENERATED_BODY()

	FAbility()
	{
		Score = 0.0f;
		ScoreThreshold = 0.0f;
		DecrementScoreBase = 0.0f;
		DecrementScoreExecuted = 0.0f;
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRuntimeFloatCurve DistanceCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Score;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ScoreThreshold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DecrementScoreBase;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DecrementScoreExecuted;

	UPROPERTY(EditAnywhere, meta = (BaseStruct = "/Script/Gilt.PostExecutionChange"))
	TArray<FInstancedStruct> AbilityScoreChanges;
};

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class GILT_API UGiltAIAbilitiesData : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	TMap<FGameplayTag, FAbility> Abilities;

	UPROPERTY(EditAnywhere)
	float ComboWindow;
};
