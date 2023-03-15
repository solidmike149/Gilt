// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GiltAttributeSet.h"
#include "NativeGameplayTags.h"
#include "GiltBasicSet.generated.h"

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Gameplay_Damage);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Gameplay_DamageImmunity);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Gameplay_DamageSelfDestruct);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Gameplay_FellOutOfWorld);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Gilt_Damage_Message);

/**
 * UGiltBasicSet
 *
 *	Class that defines attributes that are necessary for all characters.
 *	Attribute examples include: health, shields, resistances and speed.
 */
UCLASS(BlueprintType)
class GILT_API UGiltBasicSet : public UGiltAttributeSet
{
	GENERATED_BODY()

public:

	UGiltBasicSet();

	ATTRIBUTE_ACCESSORS(UGiltBasicSet, Health);
	ATTRIBUTE_ACCESSORS(UGiltBasicSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(UGiltBasicSet, MovementSpeed);

	// Delegate to broadcast when the health attribute reaches zero.
	mutable FGiltAttributeEvent OnOutOfHealth;

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	void ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const;

private:

	// The current health attribute.  The health will be capped by the max health attribute.  Health is hidden from modifiers so only executions can modify it.
	UPROPERTY(BlueprintReadOnly,  Category = "Gilt|Health", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Health;

	// The current max health attribute.  Max health is an attribute since gameplay effects can modify it.
	UPROPERTY(BlueprintReadOnly,  Category = "Gilt|Health", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxHealth;

	// Used to track when the health reaches 0.
	bool bOutOfHealth;

	// The current max health attribute.  Max health is an attribute since gameplay effects can modify it.
	UPROPERTY(BlueprintReadOnly,  Category = "Gilt|Speed", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MovementSpeed;
};
