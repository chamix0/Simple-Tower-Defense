﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "SimpleTextWidget.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "SimpleButtonWidget.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_DELEGATE(FOnButtonSelected);

UCLASS()
class SIMPLETOWERDEFENSE_API USimpleButtonWidget : public UCommonUserWidget, public Observer
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
	//colors
	UPROPERTY(EditAnywhere)
	FColor m_dayColor = FColor::White;
	UPROPERTY(EditAnywhere)
	FColor m_nightColor = FColor::Black;
	FLinearColor m_currentColor;
	FLinearColor m_targetColor;
	UPROPERTY(EditAnywhere)
	float m_ColorChangeSpeed = 5.f;

	//tower world entity
	UPROPERTY()
	UTowerWorldManager* m_TowerWorldManager = nullptr;

public:
	//action delegate
	FOnButtonSelected OnButtonSelected;

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeOnInitialized() override;
	virtual void update(const UTowerEvent event) override;

public:
	/// show widget on viewport
	UFUNCTION(BlueprintCallable)
	void Show();
	///hide widget on viewport
	UFUNCTION(BlueprintCallable)
	void Hide();

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

	void PerformSelectAction();
	//Events
	UFUNCTION(BlueprintImplementableEvent)
	void OnButtonSelectedEvent();

private:
	/// fast forward text animation
	void FastForwardText();
};