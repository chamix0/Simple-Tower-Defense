// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Basics/DayNightWidget.h"

#include "Managers/TowerWorldManager.h"
#include "Settings/GameSettings.h"

void UDayNightWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	//update colors
	m_currentColor = FMath::CInterpTo(m_currentColor, m_targetColor, InDeltaTime,
	                                  GetDefault<UGameSettings>()->ColorChangeSpeedUI);
	m_currentOppositeColor = FMath::CInterpTo(m_currentOppositeColor, m_targetOppositeColor, InDeltaTime,
	                                          GetDefault<UGameSettings>()->ColorChangeSpeedUI);
}

void UDayNightWidget::NativeOnInitialized()
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
		m_targetOppositeColor = m_TowerWorldManager->GetIsDay() ? m_nightColor : m_dayColor;
		m_currentColor = m_targetColor;
		m_currentOppositeColor = m_targetOppositeColor;
	}
	else
	{
		//initialize colors
		m_targetColor = m_dayColor;
		m_targetOppositeColor = m_nightColor;
		m_currentColor = m_targetColor;
		m_currentOppositeColor = m_targetOppositeColor;
	}
}

void UDayNightWidget::update(const UTowerEvent event)
{
	if (event == UTowerEvent::IS_NIGHT)
	{
		m_targetColor = m_nightColor;
		m_targetOppositeColor = m_dayColor;
	}
	else if (event == UTowerEvent::IS_DAY)
	{
		m_targetColor = m_dayColor;
		m_targetOppositeColor = m_nightColor;
	}
}

void UDayNightWidget::Show()
{
	SetVisibility(ESlateVisibility::Visible);
}

void UDayNightWidget::Hide()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

void UDayNightWidget::SetDayColor(FLinearColor Color)
{
	m_dayColor = Color;
	//initialize colors
	m_targetColor = m_TowerWorldManager->GetIsDay() ? m_dayColor : m_nightColor;
	m_targetOppositeColor = m_TowerWorldManager->GetIsDay() ? m_nightColor : m_dayColor;
	m_currentColor = m_targetColor;
	m_currentOppositeColor = m_targetOppositeColor;
}

void UDayNightWidget::SetNightColor(FLinearColor Color)
{
	m_nightColor = Color;
	//initialize colors
	m_targetColor = m_TowerWorldManager->GetIsDay() ? m_dayColor : m_nightColor;
	m_targetOppositeColor = m_TowerWorldManager->GetIsDay() ? m_nightColor : m_dayColor;
	m_currentColor = m_targetColor;
	m_currentOppositeColor = m_targetOppositeColor;
}
