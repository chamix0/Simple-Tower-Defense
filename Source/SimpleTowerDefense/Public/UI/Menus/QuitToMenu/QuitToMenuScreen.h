// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActionWidget.h"
#include "Components/Image.h"
#include "UI/Basics/JustButtonsScreen.h"
#include "QuitToMenuScreen.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLETOWERDEFENSE_API UQuitToMenuScreen : public UJustButtonsScreen
{
	GENERATED_BODY()

	
	
	UPROPERTY(meta=(BindWidget))
	USimpleButtonWidget* Button_Cancel;
	UPROPERTY(meta=(BindWidget))
	USimpleButtonWidget* Button_QuitToMenu;
	UPROPERTY(meta=(BindWidget))
	UCommonActionWidget* auxInputAction;
	UPROPERTY(meta=(BindWidget))
	UImage* m_blockingScreen;
protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeOnActivated() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	

private:
	//button actions
	UFUNCTION()
	void CancelButtonAction();
	virtual void HandleReturnAction() override;
	UFUNCTION()
	void QuitToMenuButtonAction();
	UFUNCTION()
	void OnInputMethodChanged(bool usingGamepad);
};
