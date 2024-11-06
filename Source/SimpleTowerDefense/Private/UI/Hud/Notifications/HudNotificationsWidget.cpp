// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Hud/Notifications/HudNotificationsWidget.h"

#include "UI/Basics/SimpleTextWidget.h"

FPopUpInfo::FPopUpInfo(): text(""), time(0)
{
}

FPopUpInfo::FPopUpInfo(FString _Text, float _time): text(_Text), time(_time)
{
}

void UHudNotificationsWidget::PushText(FString textToDisplay, float time)
{
	for (FPopUpInfo info : textQueue)
	{
		if (info.text == textToDisplay)
		{
			return;
		}
	}
	textQueue.Push(FPopUpInfo(textToDisplay, time));
	if (!StopWatch.isRunning())
	{
		ShowNextText();
	}
}


void UHudNotificationsWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	// feed the stopwatch
	StopWatch.ReceiveTick(InDeltaTime);
	//fade out when the stopwatch is not running and the widget is visible
	if (!StopWatch.isRunning() && GetRenderOpacity() > 0)
	{
		float alpha = FMath::FInterpConstantTo(GetRenderOpacity(), 0, InDeltaTime, 1);
		SetRenderOpacity(alpha);
		return;
	}
	//dont do anything when stopwatch is not running and the widget is not visible
	if (!StopWatch.isRunning())
	{
		return;
	}

	//fade in when the stopwatch is running
	if (StopWatch.isRunning() && GetRenderOpacity() < 1)
	{
		float alpha = FMath::FInterpConstantTo(GetRenderOpacity(), 1, InDeltaTime, 1);
		SetRenderOpacity(alpha);
	}

	//show next text
	if (StopWatch.isRunning() && StopWatch.GetElapsedSeconds() > currentPopUp.time)
	{
		ShowNextText();
	}
}

void UHudNotificationsWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	Hide();

	text->SetDayColor(m_dayColor);
	text->SetNightColor(m_nightColor);
}

void UHudNotificationsWidget::ShowNextText()
{
	if (!textQueue.IsEmpty())
	{
		FPopUpInfo nextText = textQueue.Pop();
		text->SetText(FText().FromString(nextText.text));
		Show();
		StopWatch.ReStart();
		currentPopUp = nextText;
		return;
	}
	//nothing to show so stop the stopwatch
	StopWatch.Reset();
	currentPopUp = FPopUpInfo();

	// text->SetText(FText());
}
