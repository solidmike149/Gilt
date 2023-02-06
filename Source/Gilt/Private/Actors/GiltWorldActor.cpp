// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/GiltWorldActor.h"

#include "Components/BoxComponent.h"


// Sets default values
AGiltWorldActor::AGiltWorldActor()
{

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>("Collision");
	RootComponent = CollisionComponent;
	CollisionComponent->SetCollisionObjectType(ECC_WorldStatic);
	CollisionComponent->SetGenerateOverlapEvents(false);
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	StaticMeshComponent->SetupAttachment(RootComponent);
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	StaticMeshComponent->SetRelativeRotation(FRotator(0.0f, 45.0f, 60.0f));
}
