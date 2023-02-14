// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GiltVerbMessage.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AbilitySystem/GiltGameplayCueManager.h"

#include "GiltVerbMessageHelpers.generated.h"

/**
 * 
 */
UCLASS()
class GILT_API UGiltVerbMessageHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable, Category = "Gilt")
	static APlayerState* GetPlayerStateFromObject(UObject* Object);

	UFUNCTION(BlueprintCallable, Category = "Gilt")
	static APlayerController* GetPlayerControllerFromObject(UObject* Object);

	UFUNCTION(BlueprintCallable, Category = "Gilt")
	static FGameplayCueParameters VerbMessageToCueParameters(const FGiltVerbMessage& Message);

	UFUNCTION(BlueprintCallable, Category = "Gilt")
	static FGiltVerbMessage CueParametersToVerbMessage(const FGameplayCueParameters& Params);
};
