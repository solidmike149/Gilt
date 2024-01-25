// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "GiltDiaryComponent.generated.h"

USTRUCT(BlueprintType)
struct FDiaryEntry : public FTableRowBase
{
	GENERATED_BODY()

	FDiaryEntry(){}

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Title;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString CategoryKey;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FText> Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UTexture2D> Icon;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UTexture2D> Image;
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDiaryEntryAdded, UGiltDiaryComponent*, Instigator, const FDiaryEntry&, DiaryEntry);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GILT_API UGiltDiaryComponent : public UActorComponent
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UDataTable* DiaryTable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame)
	TArray<FName> UnlockedEntries;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame)
	TArray<FString> UnlockedCategories;

	UPROPERTY(EditAnywhere)
	bool bIsInDebugMode;

public:	

	UGiltDiaryComponent();

	/** Returns the diary component if one exists on the specified actor. */
	UFUNCTION(BlueprintPure, Category = "Diary")
	static UGiltDiaryComponent* FindDiaryComponent(const AActor* Actor) { return (Actor ? Actor->FindComponentByClass<UGiltDiaryComponent>() : nullptr); }
	
	UFUNCTION(BlueprintCallable)
	TArray<FString> GetUnlockedCategories() const;

	UFUNCTION(BlueprintCallable)
	void AddDiaryEntry(FName EntryId);

	UFUNCTION(BlueprintCallable)
	void ClosePopUp();

	UFUNCTION(BlueprintCallable)
	void GetEntryDataByCategory(const FString& Category, TArray<FDiaryEntry>& OutData) const;

	UFUNCTION(BlueprintCallable)
	bool GetEntryById(FName Id, FDiaryEntry& Data) const;

	UPROPERTY(BlueprintAssignable)
	FOnDiaryEntryAdded OnDiaryEntryAdded;
};
