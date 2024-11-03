// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Image.h"
#include "UI/Basics/JustButtonsScreen.h"
#include "Utils/StopWatch.h"
#include "QuitToDesktopScreen.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLETOWERDEFENSE_API UQuitToDesktopScreen : public UJustButtonsScreen
{
	GENERATED_BODY()

	
	UPROPERTY(meta=(BindWidget))
	USimpleButtonWidget* Button_Cancel;
	UPROPERTY(meta=(BindWidget))
	USimpleButtonWidget* Button_QuitToDesktop;

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
	void QuitToDesktopButtonAction();
};
