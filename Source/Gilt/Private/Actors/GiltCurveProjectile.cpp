// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/GiltCurveProjectile.h"


// Sets default values
AGiltCurveProjectile::AGiltCurveProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGiltCurveProjectile::BeginPlay()
{
	Super::BeginPlay();

	if(!Curve.GetRichCurve())
	{
		SetActorTickEnabled(false);
	}
}

// Called every frame
void AGiltCurveProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Time += DeltaTime;

	if (Curve.GetRichCurveConst() && Curve.GetRichCurveConst()->GetNumKeys() > 0)
	{
		float YValue = Curve.GetRichCurveConst()->Eval(Time);

		FVector CurrentLocation = GetActorLocation();

		FVector NewLocation = FVector(CurrentLocation.X, CurrentLocation.Y + YValue, CurrentLocation.Z);
		SetActorLocation(NewLocation, true);
	}
}
