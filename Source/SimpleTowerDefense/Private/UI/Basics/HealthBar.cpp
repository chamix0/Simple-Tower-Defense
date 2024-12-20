// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Basics/HealthBar.h"

#include "Settings/GameSettings.h"

void UHealthBar::Show()
{
	SetVisibility(ESlateVisibility::Visible);
	m_currentColor=m_targetColor;
}

void UHealthBar::Hide()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

void UHealthBar::SetValue(float currentHealth, float MaxHealth)
{
	m_MainHealthBar->SetPercent(FMath::Max(0.01f, currentHealth / MaxHealth));
}

void UHealthBar::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	//get tower world manager
	m_towerWorldManager = GetWorld()->GetSubsystem<UTowerWorldManager>();
	//subscribe to publisher
	m_towerWorldManager->Subscribe(this);

	//initialize color
	m_targetColor = m_towerWorldManager->GetIsDay() ? m_dayColor : m_nightColor;
	m_currentColor = m_targetColor;
}

void UHealthBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	//interpolate color
	m_currentColor = FMath::CInterpTo(m_currentColor, m_targetColor, InDeltaTime,
	                                  GetDefault<UGameSettings>()->ColorChangeSpeed);

	m_MainHealthBar->SetFillColorAndOpacity(m_currentColor);
}

void UHealthBar::update(const UTowerEvent event)
{
	Observer::update(event);

	if (event == UTowerEvent::IS_NIGHT)
	{
		m_targetColor = m_nightColor;
	}
	else if (event == UTowerEvent::IS_DAY)
	{
		m_targetColor = m_dayColor;
	}
}
