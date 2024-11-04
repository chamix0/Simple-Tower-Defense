// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "DayNightWidget.h"
#include "SimpleTextWidget.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "SimpleButtonWidget.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_DELEGATE(FOnButtonSelected);

UCLASS()
class SIMPLETOWERDEFENSE_API USimpleButtonWidget : public UDayNightWidget
{
	GENERATED_BODY()

	//sound to play
	UPROPERTY()
	UAudioComponent* audioComponent = nullptr;
	UPROPERTY(EditAnywhere)
	USoundBase* buttonSelectedAudio = nullptr;

	//default Text
	UPROPERTY(EditAnywhere)
	FText m_DefaultText;

	//button text
	UPROPERTY(meta = (BindWidget))
	USimpleTextWidget* m_Text = nullptr;

	//image
	UPROPERTY(meta = (BindWidget))
	UImage* m_background = nullptr;

	//associated input
	UPROPERTY(meta = (BindWidget))
	USizeBox* m_inputSizeBox = nullptr;

	UPROPERTY(meta = (BindWidget))
	UCommonActionWidget* m_InputHint = nullptr;

	UPROPERTY(EditAnywhere)
	bool ShowInputHintWhenHighlighted = false;
	FText m_currentText; //current text of the button
	bool m_highlighted = false;
	bool m_mouseHighlight = false;

public:
	//action delegate
	FOnButtonSelected OnButtonSelected;

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeOnInitialized() override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

public:
	/// text to show in button
	/// @param body
	void SetText(FText body, bool completed = false);


	/// removes the text
	void ClearText();

	/// give the button default values
	void Reset();

	/// highlight or not the button
	/// @param highlighted 
	void SetHighLight(bool highlighted);
	void SetMouseHighLight(bool MouseHighlight);

	void PerformSelectAction();
	//Events
	UFUNCTION(BlueprintImplementableEvent)
	void OnButtonSelectedEvent();

private:
	/// fast forward text animation
	void FastForwardText();
};
