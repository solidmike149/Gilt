// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Components/SceneComponent.h"
#include "GameplayTagContainer.h"

#include "GiltWeakSpotComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStatusChagedDelegate, bool, bIsOpen, FGameplayEventData, Payload);

struct FGameplayEventData;
class UBoxComponent;


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent, DisplayName="WeakSpot Component"))
class GILT_API UGiltWeakSpotComponent : public USceneComponent
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

	void GameplayEventCallback(const FGameplayEventData* Payload);

	UPROPERTY(BlueprintAssignable)
	FOnStatusChagedDelegate OnStatusChanged;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bIsOpen;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* BoxCollision;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag EventTag;
};
