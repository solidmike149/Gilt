// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GiltProjectileBase.h"
#include "GiltCurveProjectile.generated.h"

UCLASS()
class GILT_API AGiltCurveProjectile : public AGiltProjectileBase
{
	GENERATED_BODY()

	AGiltCurveProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile Animation")
	FRuntimeFloatCurve Curve;

	UPROPERTY(BlueprintReadWrite)
	bool bHasHitPlayer;

private:

	float Time;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
