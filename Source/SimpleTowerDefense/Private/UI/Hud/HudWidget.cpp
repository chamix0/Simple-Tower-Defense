// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Hud/HudWidget.h"

void UHudWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	m_towerWorldManager = GetWorld()->GetSubsystem<UTowerWorldManager>();
	m_daysCount->SetText(FText::FromString("Days passed: 0"));
	m_pointsCount->SetText(FText::FromString("Points: 0"));
	m_pauseButton->SetText(FText::FromString("UNPAUSED"), true);

	//bind action to button
	m_pauseButton->OnButtonSelected.BindDynamic(this, &ThisClass::PauseAction);
}

void UHudWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UHudWidget::UpdateHealth(float currentHealth, float maxHealth)
{
	m_healthBar->SetValue(currentHealth, maxHealth);
}

void UHudWidget::SetDays(int num)
{
	m_daysCount->SetText(FText::FromString("Days passed: " + FString::FromInt(num)));
}

void UHudWidget::SetPoints(int num)
{
	m_pointsCount->SetText(FText::FromString("Points: " + FString::FromInt(num)));
}

void UHudWidget::PauseAction()
{
	m_towerWorldManager->SetPaused(!m_towerWorldManager->GetPaused());

	m_pauseButton->SetText(m_towerWorldManager->GetPaused()
		                       ? FText::FromString("PAUSED")
		                       : FText::FromString("UNPAUSED"), true);
	//show exit to main menu hint
}
