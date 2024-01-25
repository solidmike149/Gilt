// Fill out your copyright notice in the Description page of Project Settings.


#include "Diary/GiltDiaryComponent.h"

UGiltDiaryComponent::UGiltDiaryComponent()
{

}

void UGiltDiaryComponent::AddDiaryEntry(FName EntryId)
{
	if (DiaryTable == nullptr)
	{
		FString StringDebug = FString::Printf(TEXT("Set DataTable On Diary Component"));
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, StringDebug);
		return;
	}
	
	FString ContextString = "SearchForEntry";
	FDiaryEntry* Entry = DiaryTable->FindRow<FDiaryEntry>(EntryId, ContextString, true);

	if (Entry)
	{
		UnlockedEntries.Add(EntryId);

		if(!bIsInDebugMode)
		{GetOwner()->DisableInput(GetWorld()->GetFirstPlayerController());
            		
			OnDiaryEntryAdded.Broadcast(this, *Entry);
		}
		
		if (!UnlockedCategories.Contains(Entry->CategoryKey))
		{
			UnlockedCategories.Add(Entry->CategoryKey);
		}
	}
	
	else
	{
		FString StringDebug = FString::Printf(TEXT("Check Id On Interactable Actor"));
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Yellow, StringDebug);
	}
}


void UGiltDiaryComponent::ClosePopUp()
{
	GetOwner()->EnableInput(GetWorld()->GetFirstPlayerController());
}


void UGiltDiaryComponent::GetEntryDataByCategory(const FString& Category, TArray<FDiaryEntry>& OutData) const
{
	TArray<FDiaryEntry*> Entries;

	//TODO Only unlocked entries by filtering

	DiaryTable->GetAllRows(FString(""), Entries);

	for (FDiaryEntry* const& DiaryEntry : Entries)
	{
		if (DiaryEntry->CategoryKey == Category)
		{
			OutData.Add(*DiaryEntry);
		}
	}
}

bool UGiltDiaryComponent::GetEntryById(FName Id, FDiaryEntry& Data) const
{
	if (UnlockedEntries.Contains(Id))
	{
		Data = *DiaryTable->FindRow<FDiaryEntry>(Id, FString(""),true);
		return true;
	}
	
	return false;
}


TArray<FString> UGiltDiaryComponent::GetUnlockedCategories() const
{
	return UnlockedCategories;
}
