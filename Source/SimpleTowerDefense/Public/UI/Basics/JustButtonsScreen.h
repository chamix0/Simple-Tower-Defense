// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActionWidget.h"
#include "CommonActivatableWidget.h"
#include "Components/Image.h"
#include "Managers/TowerWorldManager.h"
#include "UI/BaseWidget.h"
#include "CommonInputSubsystem.h"
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
	UPROPERTY()
	UTowerWorldManager* m_towerWorldManger = nullptr;
	//hud
	UPROPERTY()
	UBaseWidget* m_BaseWidget = nullptr;

	UPROPERTY(meta=(BindWidget))
	UImage* m_mouseBlockingImage = nullptr;
	UPROPERTY(meta=(BindWidget))
	UCommonActionWidget* m_ActionWidget= nullptr;
	

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
	UFUNCTION()
	void InputChanged(bool isGamepad);

public:
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
