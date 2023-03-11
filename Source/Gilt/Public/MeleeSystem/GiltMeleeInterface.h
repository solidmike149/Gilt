// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GiltMeleeInterface.generated.h"

UINTERFACE()
class UGiltMeleeInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GILT_API IGiltMeleeInterface
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void RegisterHitboxes(const TArray<FName>& RegisteringIDs);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UnRegisterHitboxes(const TArray<FName>& UnRegisteringIDs);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UPrimitiveComponent* GetOriginComponent() const;
};
