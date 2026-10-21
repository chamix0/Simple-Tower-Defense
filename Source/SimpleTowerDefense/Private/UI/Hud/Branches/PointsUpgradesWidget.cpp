// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Hud/Branches/PointsUpgradesWidget.h"

#include "Game_Entities/Tower/Tower.h"
#include "Settings/GameSettings.h"
#include "UI/Hud/HudWidget.h"
#include "UI/Hud/Branches/UpgradeData.h"

void UPointsUpgradesWidget::Hide()
{
	SetVisibility(ESlateVisibility::Collapsed);
	
}

void UPointsUpgradesWidget::Show()
{
	SetVisibility(ESlateVisibility::Visible);
	ForceUpdateColors();
}

void UPointsUpgradesWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	//add buttons
	AddButton(m_DailyPointsUpgrade);
	AddButton(m_KillPointsMultiplierUpgrade);
	AddButton(m_MaxPointsUpgrade);
	AddButton(m_MaxGameSpeedUpgrade);


	//add actions

	m_DailyPointsUpgrade->OnButtonSelected.BindDynamic(this, &ThisClass::UpgradeButtonsAction);
	m_KillPointsMultiplierUpgrade->OnButtonSelected.BindDynamic(this, &ThisClass::UpgradeButtonsAction);
	m_MaxPointsUpgrade->OnButtonSelected.BindDynamic(this, &ThisClass::UpgradeButtonsAction);
	m_MaxGameSpeedUpgrade->OnButtonSelected.BindDynamic(this, &ThisClass::UpgradeButtonsAction);
	
	//initialize button
	m_DailyPointsUpgrade->UpdateButton();
	m_KillPointsMultiplierUpgrade->UpdateButton();
	m_MaxPointsUpgrade->UpdateButton();
	m_MaxGameSpeedUpgrade->UpdateButton();

	ActivateWidget();
}
void UPointsUpgradesWidget::UpgradeButtonsAction(USimpleButtonWidget* UpgradeButton)
{
	UUpgradeSlotWidget* UpgradeSlot= Cast<UUpgradeSlotWidget>(UpgradeButton);
	
	//check it is an upgrade button
	if (!UpgradeSlot)
	{
		return;
	}
	
	bool result = UpgradeSlot->TryUpgrade();
	
	if (!result)
	{
		return;
	}

	//apply upgrade
	UpgradeSlot->m_UpgradeData.GetDefaultObject()->ApplyUpgrade(m_towerWorldManger);
	
	//notify stats changed
	m_towerWorldManger->Notify(UTowerEvent::STATS_CHANGED);
	
	//update button
	UpgradeSlot->UpdateButton();
}
// void UPointsUpgradesWidget::DailyPointsAction(USimpleButtonWidget* button)
// {
// 	bool result = m_DailyPointsUpgrade->TryUpgrade();
// 	if (result)
// 	{
// 		m_towerWorldManger->GetTower()->GetHud()->PushNotification(FText::FromString("Daily points increased!!!"), 2.f);
// 		m_towerWorldManger->IncrementDailyPoints(GetDefault<UGameSettings>()->DailyPointsIncrement);
// 		m_towerWorldManger->Notify(UTowerEvent::STATS_CHANGED);
// 	}
// 	m_DailyPointsUpgrade->UpdateButton();
// }
//
// void UPointsUpgradesWidget::KillPointMultiplierAction(USimpleButtonWidget* button)
// {
// 	bool result = m_KillPointsMultiplierUpgrade->TryUpgrade();
// 	if (result)
// 	{
// 		m_towerWorldManger->GetTower()->GetHud()->PushNotification(FText::FromString("kill point multiplier increased!!!"), 2.f);
// 		m_towerWorldManger->IncrementKillPointMultiplier(GetDefault<UGameSettings>()->KillPointsMultiplierIncrement);
// 		m_towerWorldManger->Notify(UTowerEvent::STATS_CHANGED);
// 	}
// 	m_KillPointsMultiplierUpgrade->UpdateButton();
// }
//
// void UPointsUpgradesWidget::MaxGameSpeedAction(USimpleButtonWidget* button)
// {
// 	bool result = m_MaxGameSpeedUpgrade->TryUpgrade();
// 	if (result)
// 	{
// 		m_towerWorldManger->GetTower()->GetHud()->PushNotification(FText::FromString("Max game speed increased!!!"), 2.f);
// 		m_towerWorldManger->IncrementTimeScale(GetDefault<UGameSettings>()->GameSpeedIncrement);
// 		m_towerWorldManger->Notify(UTowerEvent::STATS_CHANGED);
// 	}
// 	m_MaxGameSpeedUpgrade->UpdateButton();
// }
//
// void UPointsUpgradesWidget::MaxPointsAction(USimpleButtonWidget* button)
// {
// 	bool result = m_MaxPointsUpgrade->TryUpgrade();
// 	if (result)
// 	{
// 		m_towerWorldManger->GetTower()->GetHud()->PushNotification(FText::FromString("Max Points increased!!!"), 2.f);
// 		m_towerWorldManger->IncrementMaxPoints(GetDefault<UGameSettings>()->MaxPointsIncrement);
// 		m_towerWorldManger->Notify(UTowerEvent::STATS_CHANGED);
// 	}
// 	m_MaxPointsUpgrade->UpdateButton();
// }

void UPointsUpgradesWidget::ForceUpdateColors()
{
	for (USimpleButtonWidget*& button : m_buttons)
	{
		button->ForceUpdateColors();
	}
}
