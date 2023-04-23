// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "ModularGameState.h"
#include "GiltGameState.generated.h"

class UGiltExperienceManagerComponent;

UCLASS()
class GILT_API AGiltGameState : public AModularGameStateBase, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

	AGiltGameState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	//~AActor interface
	virtual void PostInitializeComponents() override;
	//~End of AActor interface

	//~IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~End of IAbilitySystemInterface

	UFUNCTION(BlueprintCallable, Category = "Gilt|GameState")
	UGiltAbilitySystemComponent* GetGiltAbilitySystemComponent() const { return AbilitySystemComponent; }

private:
	
	UPROPERTY()
	UGiltExperienceManagerComponent* ExperienceManagerComponent;

	// The ability system component subobject for game-wide things (primarily gameplay cues)
	UPROPERTY(VisibleAnywhere, Category = "Gilt|GameState")
	TObjectPtr<UGiltAbilitySystemComponent> AbilitySystemComponent;
};
