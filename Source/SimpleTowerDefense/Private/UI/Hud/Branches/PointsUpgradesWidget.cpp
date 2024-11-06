// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Hud/Branches/PointsUpgradesWidget.h"

#include "Game_Entities/Tower/Tower.h"
#include "Settings/GameSettings.h"
#include "UI/Hud/HudWidget.h"

void UPointsUpgradesWidget::Hide()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

void UPointsUpgradesWidget::Show()
{
	SetVisibility(ESlateVisibility::Visible);
}

void UPointsUpgradesWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	//add buttons
	AddButton(m_DailyPointsUpgrade);
	AddButton(m_KillPointsMultiplierUpgrade);
	AddButton(m_MaxGameSpeedUpgrade);


	//add actions

	m_DailyPointsUpgrade->OnButtonSelected.BindDynamic(this, &ThisClass::DailyPointsAction);
	m_KillPointsMultiplierUpgrade->OnButtonSelected.BindDynamic(this, &ThisClass::KillPointMultiplierAction);
	m_MaxGameSpeedUpgrade->OnButtonSelected.BindDynamic(this, &ThisClass::MaxGameSpeedAction);


	//initialize button
	m_DailyPointsUpgrade->SetText(FText::FromString("Daily points"));
	m_DailyPointsUpgrade->UpdateButton();

	m_KillPointsMultiplierUpgrade->SetText(FText::FromString("Kill points multiplier"));
	m_KillPointsMultiplierUpgrade->UpdateButton();

	m_MaxGameSpeedUpgrade->SetText(FText::FromString("Max Game speed"));
	m_MaxGameSpeedUpgrade->UpdateButton();

	ActivateWidget();
}

void UPointsUpgradesWidget::DailyPointsAction()
{
	bool result = m_DailyPointsUpgrade->TryUpgrade();
	if (result)
	{
		m_towerWorldManger->GetTower()->GetHud()->PushNotification("Daily points increased!!!", 2.f);
		m_towerWorldManger->IncrementDailyPoints(GetDefault<UGameSettings>()->DailyPointsIncrement);
		m_towerWorldManger->Notify(UTowerEvent::STATS_CHANGED);
	}
	m_DailyPointsUpgrade->UpdateButton();
}

void UPointsUpgradesWidget::KillPointMultiplierAction()
{
	bool result = m_KillPointsMultiplierUpgrade->TryUpgrade();
	if (result)
	{
		m_towerWorldManger->GetTower()->GetHud()->PushNotification("kill point multiplier increased!!!", 2.f);
		m_towerWorldManger->IncrementKillPointMultiplier(GetDefault<UGameSettings>()->KillPointsMultiplierIncrement);
		m_towerWorldManger->Notify(UTowerEvent::STATS_CHANGED);
	}
	m_KillPointsMultiplierUpgrade->UpdateButton();
}

void UPointsUpgradesWidget::MaxGameSpeedAction()
{
	bool result = m_MaxGameSpeedUpgrade->TryUpgrade();
	if (result)
	{
		m_towerWorldManger->GetTower()->GetHud()->PushNotification("Max game speed increased!!!", 2.f);
		m_towerWorldManger->IncrementTimeScale(GetDefault<UGameSettings>()->GameSpeedIncrement);
		m_towerWorldManger->Notify(UTowerEvent::STATS_CHANGED);
	}
	m_MaxGameSpeedUpgrade->UpdateButton();
}
