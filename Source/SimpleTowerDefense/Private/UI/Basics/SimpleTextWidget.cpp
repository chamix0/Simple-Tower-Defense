// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Basics/SimpleTextWidget.h"

#include "Settings/GameSettings.h"



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
}

void USimpleTextWidget::SetTextDirectly(FText body, bool highlighted)
{
	//start writing
	SetText(body);

	//complete the writing
	FastForwardText();

	//set highlighted
	m_highlighted = highlighted;
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


void USimpleTextWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void USimpleTextWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	//feed the stopwatch
	StopWatch.ReceiveTick(InDeltaTime);

	//write text
	WriteText();

	//update colors
	m_TextBlock->SetColorAndOpacity(m_highlighted ? m_currentOppositeColor : m_currentColor);
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
