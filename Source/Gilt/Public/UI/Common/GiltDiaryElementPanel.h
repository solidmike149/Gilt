// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CommonActivatableWidget.h"

#include "GiltDiaryElementPanel.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class GILT_API UGiltDiaryElementPanel : public UCommonActivatableWidget
{
	GENERATED_BODY()

	
	UFUNCTION(BlueprintCallable, Category = TabList)
	virtual void SetListeningForInput(bool bShouldListen);


protected:
	
	// UUserWidget interface
	virtual void NativeConstruct() override;
	// End UUserWidget

	virtual void UpdateBindings();

	UFUNCTION(BlueprintImplementableEvent)
	void K2_HandleNextTabAction();

	UFUNCTION(BlueprintImplementableEvent)
	void K2_HandlePreviousTabAction();

	/** The input action to listen for causing the next tab to be selected */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PageSwitcher, meta = (RowType = CommonInputActionDataBase))
	FDataTableRowHandle NextTabInputActionData;

	/** The input action to listen for causing the previous tab to be selected */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PageSwitcher, meta = (RowType = CommonInputActionDataBase))
	FDataTableRowHandle PreviousTabInputActionData;

	/** Whether to register to handle tab list input immediately upon construction */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PageSwitcher, meta = (ExposeOnSpawn = "true"))
	bool bAutoListenForInput;
	
	/** Is the tab list currently listening for tab input actions? */
	bool bIsListeningForInput = false;

private:

	void HandleNextTabAction();
	void HandlePreviousTabAction();

	FUIActionBindingHandle NextTabActionHandle;
	FUIActionBindingHandle PrevTabActionHandle;
};
