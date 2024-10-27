// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "UI/BaseWidget.h"
#include "JustButtonsScreen.generated.h"

class USimpleButtonWidget;
/**
 * 
 */
UCLASS()
class SIMPLETOWERDEFENSE_API UJustButtonsScreen : public UCommonActivatableWidget
{
	GENERATED_BODY()

protected:
	//hud
	UPROPERTY()
	UBaseWidget* m_BaseWidget = nullptr;

	//buttons
	UPROPERTY()
	TArray<USimpleButtonWidget*> m_buttons;

	//current button index
	int buttonIndex = 0;



public:
	/// Called when the widget is activated
	UFUNCTION(BlueprintImplementableEvent)
	void OnWidgetActivated();
	UFUNCTION(BlueprintImplementableEvent)
	void OnPrevButtonSelected();
	UFUNCTION(BlueprintImplementableEvent)
	void OnNextButtonSelected();

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeOnActivated() override;
	virtual void NativeOnDeactivated() override;
	/// Add a button to the array
	/// @param button 
	void AddButton(USimpleButtonWidget* button);

	/// Delete a button to the array
	/// @param index 
	void DeleteButton(int index);
	void DeleteAllButtons();
	//handle actions
	UFUNCTION(BlueprintCallable)
	virtual void HandlePrevAction();
	UFUNCTION(BlueprintCallable)
	virtual void HandleNextAction();
	UFUNCTION(BlueprintCallable)
	virtual void HandleSelectAction();
	UFUNCTION(BlueprintCallable)
	virtual void HandleReturnAction();
	
	void UpdateSelectedButton(int index);
};
