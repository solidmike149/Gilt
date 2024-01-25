// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Common/GiltDiaryElementPanel.h"

#include "Input/CommonUIInputTypes.h"

void UGiltDiaryElementPanel::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (bAutoListenForInput)
	{
		SetListeningForInput(true);
	}
}


void UGiltDiaryElementPanel::SetListeningForInput(bool bShouldListen)
{
	if (GetUISubsystem() == nullptr)
	{
		// Shutting down
		return;
	}

	if (bShouldListen != bIsListeningForInput)
	{
		bIsListeningForInput = bShouldListen;
		UpdateBindings();
	}
}


void UGiltDiaryElementPanel::UpdateBindings()
{
	// New input system binding flow
	if (bIsListeningForInput)
	{
		NextTabActionHandle = RegisterUIActionBinding(FBindUIActionArgs(NextTabInputActionData, false, FSimpleDelegate::CreateUObject(this, &UGiltDiaryElementPanel::HandleNextTabAction)));
		PrevTabActionHandle = RegisterUIActionBinding(FBindUIActionArgs(PreviousTabInputActionData, false, FSimpleDelegate::CreateUObject(this, &UGiltDiaryElementPanel::HandlePreviousTabAction)));
	}
	else
	{
		NextTabActionHandle.Unregister();
		PrevTabActionHandle.Unregister();
	}
}


void UGiltDiaryElementPanel::HandleNextTabAction()
{
	K2_HandleNextTabAction();
}


void UGiltDiaryElementPanel::HandlePreviousTabAction()
{
	K2_HandlePreviousTabAction();
}

