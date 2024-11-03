// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Basics/SimpleButtonWidget.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/AudioComponent.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Basics/SimpleTextWidget.h"
#include "Utils/MathUtils.h"

void USimpleButtonWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	//update colors
	FLinearColor finalColor = m_targetColor;
	if (m_highlighted || m_mouseHighlight)
	{
		finalColor = m_targetColor == m_dayColor ? m_nightColor : m_dayColor;
	}
	m_currentColor = FMath::CInterpTo(m_currentColor, finalColor, InDeltaTime, m_ColorChangeSpeed);
	m_background->SetColorAndOpacity(m_currentColor);
	m_InputHint->IconRimBrush.TintColor = m_currentColor;
}

void USimpleButtonWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();


	//set initial text
	SetText(m_DefaultText);

	//get game manager
	m_TowerWorldManager = GetWorld()->GetSubsystem<UTowerWorldManager>();
	if (m_TowerWorldManager != nullptr)
	{
		//subscribe to world manager
		m_TowerWorldManager->Subscribe(this);


		//initialize colors

		m_targetColor = m_TowerWorldManager->GetIsDay() ? m_dayColor : m_nightColor;

		m_currentColor = m_targetColor;
	}
	else
	{
		//initialize colors
		m_targetColor = m_dayColor;
		m_currentColor = m_targetColor;
	}
}

void USimpleButtonWidget::update(const UTowerEvent event)
{
	if (event == UTowerEvent::IS_NIGHT)
	{
		m_targetColor = m_nightColor;
	}
	else if (event == UTowerEvent::IS_DAY)
	{
		m_targetColor = m_dayColor;
	}
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


void USimpleButtonWidget::Show()
{
	SetVisibility(ESlateVisibility::Visible);
}

void USimpleButtonWidget::Hide()
{
	SetVisibility(ESlateVisibility::Hidden);
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

void USimpleButtonWidget::FastForwardText()
{
	m_Text->FastForwardText();
}
