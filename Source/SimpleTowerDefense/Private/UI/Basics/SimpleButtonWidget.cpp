// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Basics/SimpleButtonWidget.h"

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

	//current position
	float currentX = GetRenderTransform().Translation.X;

	//update position
	SetRenderTranslation(FVector2D(FMath::FInterpTo(currentX, m_visible ? m_offset : -1, InDeltaTime,5), 0));
	
	//update alpha
	m_fading
		? SetRenderOpacity(FMath::FInterpTo(GetRenderOpacity(), 0.f, InDeltaTime,5))
		: SetRenderOpacity(FMath::Min(MathUtils::NormalizeBetweenValues(currentX, 0, m_offset), m_MaxAlpha));

	//hide widget
	if ((currentX < 0 && !m_visible) || GetRenderOpacity() <= 0.05f && m_fading)
	{
		if (m_fading)
		{
			SetVisibility(ESlateVisibility::Collapsed);
		}
		
		//reset all the values
		Reset();
	}
}

void USimpleButtonWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	//set initial text
	SetText(m_DefaultText);
}

void USimpleButtonWidget::Show()
{
	SetVisibility(ESlateVisibility::Visible);
	m_visible = true;
}

void USimpleButtonWidget::Hide()
{
	SetVisibility(ESlateVisibility::Hidden);
	m_visible = false;
}

void USimpleButtonWidget::Collapse()
{
	SetVisibility(ESlateVisibility::Collapsed);
	m_visible = false;
}

void USimpleButtonWidget::HideAnimation()
{
	m_visible = false;
}

void USimpleButtonWidget::FadeOut()
{
	m_fading = true;
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

void USimpleButtonWidget::SetOffset(float offset)
{
	m_offset = offset;
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
	m_visible = false;
	m_fading = 0;
}

void USimpleButtonWidget::SetHighLight(bool highlighted)
{
	if (highlighted)
	{
		m_Text->SetTextDirectly(m_currentText);
		SetButtonValuesforHighlight(ESlateVisibility::Visible, m_highlightTexture);
	}
	else
	{
		m_Text->SetTextDirectly(m_currentText);
		SetButtonValuesforHighlight(ESlateVisibility::Hidden, m_normalTexture);
	}
}

void USimpleButtonWidget::SetNormalTextStyle(FString style)
{
	m_normalStyle = style;
}

void USimpleButtonWidget::SetHighlightTextStyle(FString style)
{
	m_highlightedStyle = style;
}

void USimpleButtonWidget::SetNormalBackground(UTexture2D* texture)
{
	m_normalTexture = texture;
}

void USimpleButtonWidget::SetHighlightBackground(UTexture2D* texture)
{
	m_highlightTexture = texture;
}

void USimpleButtonWidget::SetMaxAlpha(float alpha)
{
	m_MaxAlpha = alpha;
}

bool USimpleButtonWidget::FinishedMoving()
{
	return /*abs(GetRenderTransform().Translation.X - m_offset) < 5.f*/GetRenderTransform().Translation.X > m_offset * 2
		/
		3.f || GetVisibility() == ESlateVisibility::Collapsed;
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

void USimpleButtonWidget::SetButtonValuesforHighlight(ESlateVisibility HintVisibility, UTexture2D* texture)
{
	//hide input hint
	if (m_showInputWhenHighlighted)
	{
		m_inputSizeBox->SetVisibility(HintVisibility);
	}

	//put normal texture
	if (m_highlightTexture != nullptr)
	{
		m_background->SetBrushFromTexture(texture);
	}
}
