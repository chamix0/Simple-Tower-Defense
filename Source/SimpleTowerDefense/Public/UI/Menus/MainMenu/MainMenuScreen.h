// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Overlay.h"
#include "UI/Basics/JustButtonsScreen.h"
#include "MainMenuScreen.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLETOWERDEFENSE_API UMainMenuScreen : public UJustButtonsScreen
{
	GENERATED_BODY()
	

    	//quit to menu screen
    	// UPROPERTY(EditAnywhere, meta=(DisplayName = "Widget quit to menu class"))
    	// TSubclassOf<UQuitToDesktopScreen> QuitToDesktopWidgetClass;
	    
    
    	//buttons
    	UPROPERTY(meta=(BindWidget))
    	USimpleButtonWidget* Button_PlayGame;
    	UPROPERTY(meta=(BindWidget))
    	USimpleButtonWidget* Button_QuitToDeskTop;
    
    	//pre screen
    	UPROPERTY(meta=(BindWidget))
    	UOverlay* m_PreScreenOverlay = nullptr;
    
    	//values
    	bool m_onPreTittleScreen = true;
    
    protected:
    	virtual void NativeOnInitialized() override;
    	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
    	virtual void NativeOnActivated() override;
    
    public:

    private:
    	//override handle actions
    	virtual void HandleReturnAction() override;
    	virtual void HandleSelectAction() override;
    	virtual void HandleNextAction() override;
    	virtual void HandlePrevAction() override;
	
    	//button actions
    	UFUNCTION()
    	void PlayGameButtonAction();
    	UFUNCTION()
    	void QuitButtonAction();
};
