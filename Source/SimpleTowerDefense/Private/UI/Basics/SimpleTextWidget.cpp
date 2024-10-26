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

void USimpleTextWidget::SetText(FText body)
{
	//set the current text to write but being parsed on the first place to make the writing easier
	currentText = body.ToString();

	//reset values
	currentIndex = 0;
	textBuffer = "";

	//start timer with an offset
	StopWatch.Start();
	StopWatch.AddElapsedTime(1);

	//event of start writting text
	OnTextStartsWritting();
}

void USimpleTextWidget::SetTextDirectly(FText body)
{
	//start writing
	SetText(body);

	//complete the writing
	FastForwardText();
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

	//call fast forwad event
	OnTextFastForward();

	//call fast forward event
	OnTextEndsWritting();
}

void USimpleTextWidget::SetTimePerCharacter(float value)
{
	timePerCharacter = value;
}

void USimpleTextWidget::SetCharctersPerUpdate(int value)
{
	charactersPerUpdate = value;
}


void USimpleTextWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	//feed the stopwatch
	StopWatch.ReceiveTick(InDeltaTime);

	//write text
	WriteText();
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

				//call completed event
				OnTextEndsWritting();
				return;
			}
		}
	}
}
