// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"

#include "GiltMeleeComponent.generated.h"

class UGameplayEffect;

UENUM(BlueprintType)
enum class ETraceShape : uint8
{
	Box,
	Sphere,
	Capsule
};

USTRUCT()
struct GILT_API FMeleeCollisionData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ETraceShape Shape;

	/* The socket from which we originate the trace */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName SocketName;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "Shape==ETraceShape::Capsule", EditConditionHides))
	float CapsuleHalfHeight;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "Shape==ETraceShape::Capsule", EditConditionHides))
	float CapsuleRadius;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "Shape==ETraceShape::Sphere", EditConditionHides))
	float SphereRadius;

	UPROPERTY(EditAnywhere, meta = (EditCondition= "Shape==ETraceShape::Box", EditConditionHides))
	FVector BoxExtent;
};


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), DisplayName= "Melee Component")
class GILT_API UGiltMeleeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UGiltMeleeComponent();

	UFUNCTION(BlueprintCallable)
	void SetupComponent(UPrimitiveComponent* InPrimitiveComponent);

	UFUNCTION(BlueprintCallable)
	void RegisterHitboxes(TArray<FName> NewHitboxNames);

	//Unregister active Hitboxes, return true if there are no active hitboxes
	UFUNCTION(BlueprintCallable)
	bool UnRegisterHitboxes(TArray<FName> InHitboxNames);

	UFUNCTION(BlueprintCallable)
	UPrimitiveComponent* GetPrimitiveComponent() const;
	
private:

	void PerformMelee();

	void SweepMultiMelee(FMeleeCollisionData* HitBox,TArray<FHitResult> HitResults);

	void SendMeleeHitEvent(const FHitResult& HitResult, AActor* ActorHit);

protected:

	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/Gilt.MeleeCollisionData"))
	UDataTable* HitboxesData;

	UPROPERTY(EditDefaultsOnly, Category = "Melee")
	FGameplayTag HitEventTag;

	UPROPERTY(EditAnywhere, Category = "Melee")
	float TracePeriod;

	UPROPERTY(EditDefaultsOnly, Category = "Melee")
	TEnumAsByte<ECollisionChannel> CollisionChannel;

	UPROPERTY(EditDefaultsOnly, Category = "Melee|Debug")
	bool bDebug;

	UPROPERTY(EditDefaultsOnly, Category = "Melee|Debug", meta=(EditCondition="bDebug"))
	float DebugDuration;
	
	UPROPERTY(EditDefaultsOnly, Category = "Melee|Debug", meta=(EditCondition="bDebug"))
	FColor DebugTraceColor;

private:

	UPROPERTY(Transient)
	UPrimitiveComponent* OriginComponent;

	TArray<FMeleeCollisionData*> HitBoxes;

	UPROPERTY()
	TSet<AActor*> HitActors;
	
	FTimerHandle TimerHandle;
};
