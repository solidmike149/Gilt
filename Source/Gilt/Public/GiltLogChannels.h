// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

GILT_API DECLARE_LOG_CATEGORY_EXTERN(LogGilt, Log, All);
GILT_API DECLARE_LOG_CATEGORY_EXTERN(LogGiltExperience, Log, All);
GILT_API DECLARE_LOG_CATEGORY_EXTERN(LogGiltAbilitySystem, Log, All);
GILT_API DECLARE_LOG_CATEGORY_EXTERN(LogGiltUI, Log, All);

GILT_API FString GetClientServerContextString(UObject* ContextObject = nullptr);

static void LogOnScreen(UObject* WorldContext, FString Msg, FColor Color = FColor::White, float Duration = 5.0f)
{
	if (!ensure(WorldContext))
	{
		return;
	}

	UWorld* World = WorldContext->GetWorld();
	if (!ensure(World))
	{
		return;
	}
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, Duration, Color, Msg);
	}
}
