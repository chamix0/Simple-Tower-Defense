// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Basics/SimpleButtonWidget.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/AudioComponent.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Kismet/GameplayStatics.h"
#include "Settings/GameSettings.h"
#include "UI/Basics/SimpleTextWidget.h"
#include "Utils/MathUtils.h"

void USimpleButtonWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	UpdateColors();
}

void USimpleButtonWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();


	m_Text->SetDayColor(m_nightColor);
	m_Text->SetNightColor(m_dayColor);

	//set initial text
	SetText(m_DefaultText);
}


void USimpleButtonWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
	SetMouseHighLight(true);
}

void USimpleButtonWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
	SetMouseHighLight(false);
}

FReply USimpleButtonWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		PerformSelectAction();
	}

	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}


void USimpleButtonWidget::SetText(FText body, bool completed)
{
	m_currentText = body;
	if (completed)
	{
		m_Text->SetTextDirectly(body);
	}
	else
	{
		m_Text->SetText(body);
	}
}


void USimpleButtonWidget::ClearText()
{
	m_Text->SetText(FText::FromString(""));
}

void USimpleButtonWidget::Reset()
{
	SetRenderTranslation(FVector2D(0, 0));
	SetRenderOpacity(0);
	SetVisibility(ESlateVisibility::Collapsed);
}

void USimpleButtonWidget::SetHighLight(bool highlighted)
{
	m_Text->SetTextDirectly(m_currentText, highlighted || m_mouseHighlight);
	m_highlighted = highlighted;
	m_inputSizeBox->SetRenderOpacity(ShowInputHintWhenHighlighted ? highlighted || m_mouseHighlight : false);
}

void USimpleButtonWidget::SetMouseHighLight(bool MouseHighlight)
{
	m_mouseHighlight = MouseHighlight;
	m_Text->SetTextDirectly(m_currentText, MouseHighlight || m_highlighted);
	m_inputSizeBox->SetRenderOpacity(ShowInputHintWhenHighlighted ? MouseHighlight || m_highlighted : false);
}

void USimpleButtonWidget::PerformSelectAction()
{
	//call blueprint event
	OnButtonSelectedEvent();
	//play sound
	if (buttonSelectedAudio != nullptr)
	{
		UGameplayStatics::SpawnSound2D(this, buttonSelectedAudio, 1)->Play();
	}

	//execute action binded to button
	bool executed = OnButtonSelected.ExecuteIfBound();
}

void USimpleButtonWidget::UpdateColors()
{
	//update colors
	m_background->SetColorAndOpacity(m_highlighted || m_mouseHighlight ? m_currentOppositeColor : m_currentColor);
	FLinearColor finalColor = m_highlighted || m_mouseHighlight ? m_currentColor : m_currentOppositeColor;

	// m_InputHint->IconRimBrush.TintColor = m_highlighted || m_mouseHighlight ? m_currentColor :m_currentOppositeColor ;
	m_InputHint->IconRimBrush.TintColor = finalColor == FLinearColor(1, 1, 1, 1)
		                                      ? FLinearColor(0, 0, 0, 0)
		                                      : finalColor;
}

void USimpleButtonWidget::ForceUpdateColors()
{
	//update colors
	m_currentColor = m_targetColor;
	m_currentOppositeColor = m_targetOppositeColor;
	m_background->SetColorAndOpacity(m_highlighted || m_mouseHighlight ? m_targetOppositeColor : m_targetColor);
	FLinearColor finalColor = m_highlighted || m_mouseHighlight ? m_targetColor : m_targetOppositeColor;

	// m_InputHint->IconRimBrush.TintColor = m_highlighted || m_mouseHighlight ? m_currentColor :m_currentOppositeColor ;
	m_InputHint->IconRimBrush.TintColor = finalColor == FLinearColor(1, 1, 1, 1)
		                                      ? FLinearColor(0, 0, 0, 0)
		                                      : finalColor;
}

void USimpleButtonWidget::FastForwardText()
{
	m_Text->FastForwardText();
}
