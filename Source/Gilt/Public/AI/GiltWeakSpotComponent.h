// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Components/BoxComponent.h"
#include "GameplayTagContainer.h"

#include "GiltWeakSpotComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStatusChagedDelegate, bool, bIsOpen, FGameplayEventData, Payload);

struct FGameplayEventData;
class UBoxComponent;


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent, DisplayName="WeakSpot Component"))
class GILT_API UGiltWeakSpotComponent : public UBoxComponent
{
	GENERATED_BODY()

public:

	UGiltWeakSpotComponent();

	UFUNCTION(BlueprintPure, Category = "Gilt|AI")
	static UGiltWeakSpotComponent* FindWeakSpotComponent(const AActor* Actor) { return (Actor ? Actor->FindComponentByClass<UGiltWeakSpotComponent>() : nullptr); }

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintAssignable)
	FOnStatusChagedDelegate OnStatusChanged;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bIsOpen;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag EventTag;

	void GameplayEventCallback(const FGameplayEventData* Payload);
};
