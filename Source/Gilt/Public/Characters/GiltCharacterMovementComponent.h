// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GiltCharacterMovementComponent.generated.h"

GILT_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Gameplay_MovementStopped);
GILT_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Gameplay_RotationStopped);

/**
 * UGiltCharacterMovementComponent
 *
 *	The base character movement component class used by this project.
 */
UCLASS(Config = Game)
class GILT_API UGiltCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:

	UGiltCharacterMovementComponent();
	
	//~UMovementComponent interface
	virtual FRotator GetDeltaRotation(float DeltaTime) const override;
	virtual float GetMaxSpeed() const override;
	//~End of UMovementComponent interface
};
