// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeSystem/GiltMeleeComponent.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "DrawDebugHelpers.h"
#include "GiltLogChannels.h"


UGiltMeleeComponent::UGiltMeleeComponent()
{
	TracePeriod = 0.1f;

	bDebug = false;
	DebugDuration = 0.5;
	DebugTraceColor = FColor::Red;
}

void UGiltMeleeComponent::SetupComponent(UPrimitiveComponent* InPrimitiveComponent)
{
	if (InPrimitiveComponent)
	{
		OriginComponent = InPrimitiveComponent;
	}
	else
	{
		UE_LOG(LogGilt, Error, TEXT("GiltMeleeComponent::SetupComponent: Invalid primitive component"));
	}
}

void UGiltMeleeComponent::RegisterHitboxes(TArray<FName> NewHitboxNames)
{
	for (FName HitboxName : NewHitboxNames)
	{
		FMeleeCollisionData* MeleeCollision = HitboxesData->FindRow<FMeleeCollisionData>(HitboxName,FString());
		if (MeleeCollision)
		{
			HitBoxes.Add(MeleeCollision);
		}
	}
	
	if(!TimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UGiltMeleeComponent::PerformMelee, TracePeriod, true, 0.0f);
	}
}

void UGiltMeleeComponent::PerformMelee()
{
	for (FMeleeCollisionData* HitBox : HitBoxes)
	{
		TArray<FHitResult> HitResults;
		SweepMultiMelee(HitBox, HitResults);
		
		for (const FHitResult& HitResult : HitResults)
		{
			AActor* ActorHit = HitResult.GetActor();

			// Use HitActors as a TSet for O(log N) retrieval
			if (!HitActors.Contains(ActorHit))
			{
				HitActors.Add(ActorHit);
				
				SendMeleeHitEvents(HitResult, ActorHit);
			}
		}
	}
}

void UGiltMeleeComponent::SweepMultiMelee(FMeleeCollisionData* HitBox, TArray<FHitResult>& HitResults)
{
	FName SocketName = HitBox->SocketName;

	if(!ensure(OriginComponent))
	{
		UE_LOG(LogGilt, Error, TEXT("GiltMeleeComponent::SetupComponent: Invalid primitive component"));
		return;
	}
	
	FVector StartLocation = OriginComponent->GetSocketLocation(SocketName);
	FQuat Rotation = OriginComponent->GetSocketQuaternion(SocketName);
	UWorld* World = GetWorld();
	
	FCollisionShape Shape;
	
	FVector EndLocation;

	
	switch (HitBox->Shape)
	{
	case ETraceShape::Box:
		Shape.SetBox(FVector3f(HitBox->BoxExtent));
		EndLocation = StartLocation + (Rotation.Vector() * HitBox->BoxExtent.X);
		if (bDebug)
		{
			FVector DebugCenterLocation = StartLocation + (Rotation.Vector() * HitBox->BoxExtent.X / 2);
			DrawDebugBox(World, DebugCenterLocation, HitBox->BoxExtent, Rotation, DebugTraceColor, false, DebugDuration);
		}
		break;
	
	case ETraceShape::Sphere:
		Shape.SetSphere(HitBox->SphereRadius);
		if (bDebug)
		{
			DrawDebugSphere(World, StartLocation, HitBox->SphereRadius, 16, DebugTraceColor, false, DebugDuration);
		}
		break;
	
	case ETraceShape::Capsule:
		Shape.SetCapsule(HitBox->CapsuleRadius, HitBox->CapsuleHalfHeight);
		if (bDebug)
		{
			EndLocation = StartLocation + (Rotation.Vector() * HitBox->CapsuleHalfHeight);
			DrawDebugCapsule(World, StartLocation, HitBox->CapsuleHalfHeight, HitBox->CapsuleRadius, Rotation, DebugTraceColor, false, DebugDuration);
		}
		break;
		
	default:
		UE_LOG(LogTemp, Warning, TEXT("Case Undefined"))
		break;
	}
	
	World->SweepMultiByChannel(HitResults , StartLocation, EndLocation, Rotation, CollisionChannel, Shape);
}

void UGiltMeleeComponent::SendMeleeHitEvents(const FHitResult& HitResult, AActor* ActorHit)
{
	UAbilitySystemComponent* AbilitySystemComponent = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwner());
	if (AbilitySystemComponent != nullptr && IsValidChecked(AbilitySystemComponent))
	{
		FScopedPredictionWindow NewScopedWindow(AbilitySystemComponent, true);
		FGameplayEventData Payload;
		Payload.Target = ActorHit;
		AbilitySystemComponent->HandleGameplayEvent(HitEventTag, &Payload);
		AbilitySystemComponent->HandleGameplayEvent(HitFeedbackTag, &Payload);
	}
}

bool UGiltMeleeComponent::UnRegisterHitboxes(TArray<FName> InHitboxNames)
{
	for (FName HitboxName : InHitboxNames)
	{
		FMeleeCollisionData* MeleeCollision = HitboxesData->FindRow<FMeleeCollisionData>(HitboxName,FString());
		if (MeleeCollision)
		{
			HitBoxes.RemoveSingleSwap(MeleeCollision);
		}
	}
	if (HitBoxes.IsEmpty())
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		HitActors.Empty();
		return true;
	}
	return false;
}

UPrimitiveComponent* UGiltMeleeComponent::GetPrimitiveComponent() const
{
	return OriginComponent;
}
