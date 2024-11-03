// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Basics/SimpleTextWidget.h"

void USimpleTextWidget::Show()
{
	SetVisibility(ESlateVisibility::Visible);
}

void USimpleTextWidget::Hide()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

void USimpleTextWidget::SetText(FText body, bool highlighted)
{
	//set the current text to write but being parsed on the first place to make the writing easier
	currentText = body.ToString();

	//reset values
	currentIndex = 0;
	textBuffer = "";

	//start timer with an offset
	StopWatch.Start();
	StopWatch.AddElapsedTime(1);

	//set highlighted
	m_highlighted = highlighted;

	//set target color
	m_targetColor = highlighted ? m_dayColor : m_nightColor;
}

void USimpleTextWidget::SetTextDirectly(FText body, bool highlighted)
{
	//start writing
	SetText(body);

	//complete the writing
	FastForwardText();

	//set highlighted
	m_highlighted = highlighted;

	//set target color
	m_targetColor = highlighted ? m_nightColor : m_dayColor;
}

bool USimpleTextWidget::IsWrittingText()
{
	return StopWatch.isRunning();
}

void USimpleTextWidget::FastForwardText()
{
	//stop and reset the stopwatch
	StopWatch.Reset();

	//set the full text
	m_TextBlock->SetText(FText().FromString(currentText));
}

void USimpleTextWidget::SetTimePerCharacter(float value)
{
	timePerCharacter = value;
}

void USimpleTextWidget::SetCharctersPerUpdate(int value)
{
	charactersPerUpdate = value;
}

void USimpleTextWidget::SetHighlighted(bool value)
{
	m_highlighted = value;
}

void USimpleTextWidget::SetDayColor(FLinearColor Color)
{
	m_dayColor = Color;
}

void USimpleTextWidget::SetNightColor(FLinearColor Color)
{
	m_nightColor = Color;
}


void USimpleTextWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
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

void USimpleTextWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	//feed the stopwatch
	StopWatch.ReceiveTick(InDeltaTime);

	//write text
	WriteText();

	//update colors
	m_currentColor = FMath::CInterpTo(m_currentColor, m_targetColor, InDeltaTime, m_ColorChangeSpeed);
	m_TextBlock->SetColorAndOpacity(m_currentColor);
}


void USimpleTextWidget::WriteText()
{
	//return if the stopwhatch is not running or there is no text to writte
	if (!StopWatch.isRunning() /*|| currentText.IsEmpty()*/)
	{
		return;
	}

	//current elapsed seconds
	float elapsedTime = StopWatch.GetElapsedSeconds();
	if (elapsedTime > timePerCharacter)
	{
		//write N characters per update
		for (int i = 0; i < charactersPerUpdate; ++i)
		{
			//dont exceed the maximum text letters
			if (currentIndex < currentText.Len())
			{
				//current character to be proccessed
				char currentChar = currentText[currentIndex];

				//add char to buffer
				textBuffer.AppendChar(currentChar);

				//add random end character to make construction effect
				char randCharEnd = FMath::RandRange(33, 59);
				m_TextBlock->SetText(FText().FromString(textBuffer + randCharEnd));

				//update index
				++currentIndex;

				//restart stopwatch
				StopWatch.ReStart();
			}
			else
			{
				//complete the text
				FastForwardText();

				return;
			}
		}
	}
}

void USimpleTextWidget::update(const UTowerEvent event)
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
