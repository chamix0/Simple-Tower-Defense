// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BaseWidget.h"

#include "UI/Hud/HudWidget.h"


UCommonActivatableWidget* UBaseWidget::PushWidget(TSubclassOf<UCommonActivatableWidget> widget)
{
	if (m_baseStack != nullptr)
	{
		return m_baseStack->AddWidget(widget);
	}
	return nullptr;
}

void UBaseWidget::RemoveWidget(UCommonActivatableWidget* widgetToRemove)
{
	if (m_baseStack != nullptr)
	{
		m_baseStack->RemoveWidget(*widgetToRemove);
	}
}

bool UBaseWidget::IsUpperMostWidget(UCommonActivatableWidget* widget)
{
	UCommonActivatableWidget* activeWidget = m_baseStack->GetActiveWidget();
	return activeWidget == widget;
}

UHudWidget* UBaseWidget::GetHudWidget()
{
	UHudWidget* Widget = Cast<UHudWidget>(m_baseStack->GetRootContent());
	return Widget;
}
