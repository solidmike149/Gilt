// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/GameFrameworkComponent.h"
#include "GiltHealthComponent.generated.h"

class UGiltBasicSet;
class UGiltAbilitySystemComponent;
struct FGameplayEffectSpec;
struct FOnAttributeChangeData;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGiltHealth_DeathEvent, AActor*, OwningActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FGiltHealth_AttributeChanged, UGiltHealthComponent*, HealthComponent, float, OldValue, float, NewValue, AActor*, Instigator);

/**
 * EGiltDeathState
 *
 *	Defines current state of death.
 */
UENUM(BlueprintType)
enum class EGiltDeathState : uint8
{
	NotDead = 0,
	DeathStarted,
	DeathFinished
};

/**
 * UTiHealthComponent
 *
 *	An actor component used to handle anything related to health.
 */
UCLASS(Blueprintable, Meta=(BlueprintSpawnableComponent))
class GILT_API UGiltHealthComponent : public UGameFrameworkComponent
{
	GENERATED_BODY()

public:

	UGiltHealthComponent(const FObjectInitializer& ObjectInitializer);
	
	/** Returns the health component if one exists on the specified actor. */
	UFUNCTION(BlueprintPure, Category = "Health")
	static UGiltHealthComponent* FindHealthComponent(const AActor* Actor) { return (Actor ? Actor->FindComponentByClass<UGiltHealthComponent>() : nullptr); }
	
	/** Initialize the component using an ability system component. */
	UFUNCTION(BlueprintCallable, Category = "Health")
	void InitializeWithAbilitySystem(UGiltAbilitySystemComponent* InASC);
	
	/** Uninitialize the component, clearing any references to the ability system. */
	UFUNCTION(BlueprintCallable, Category = "Health")
	void UninitializeFromAbilitySystem();
	
	/** Returns the current health value. */
	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHealth() const;
	
	/** Returns the current maximum health value. */
	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetMaxHealth() const;
	
	/** Delegate fired when the health value has changed. */
	UPROPERTY(BlueprintAssignable)
	FGiltHealth_AttributeChanged OnHealthChanged;

	/** Delegate fired when the max health value has changed. */
	UPROPERTY(BlueprintAssignable)
	FGiltHealth_AttributeChanged OnMaxHealthChanged;

protected:

	virtual void OnUnregister() override;

	void ClearGameplayTags();

	virtual void HandleHealthChanged(const FOnAttributeChangeData& ChangeData);
	virtual void HandleMaxHealthChanged(const FOnAttributeChangeData& ChangeData);
	virtual void HandleOutOfHealth(AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec& DamageEffectSpec, float DamageMagnitude);
	
	// Ability system used by this component.
	UPROPERTY()
	UGiltAbilitySystemComponent* AbilitySystemComponent;

	// Health set used by this component.
	UPROPERTY()
	const UGiltBasicSet* HealthSet;
	
};
