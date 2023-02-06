// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GiltWorldActor.generated.h"

class UBoxComponent;
UCLASS()
class GILT_API AGiltWorldActor : public AActor
{
	GENERATED_BODY()

public:
	
	AGiltWorldActor();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* CollisionComponent;

};
