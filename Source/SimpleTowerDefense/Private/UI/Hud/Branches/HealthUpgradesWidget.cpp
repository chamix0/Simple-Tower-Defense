// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Hud/Branches/HealthUpgradesWidget.h"

#include "UI/Hud/HudWidget.h"
#include "UI/Hud/Branches/UpgradeData.h"

void UHealthUpgradesWidget::Hide()
{
	SetVisibility(ESlateVisibility::Collapsed);
	
}

void UHealthUpgradesWidget::Show()
{
	SetVisibility(ESlateVisibility::Visible);
	ForceUpdateColors();

}

void UHealthUpgradesWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	//add buttons
	AddButton(m_MaxHealthUpgrade);
	AddButton(m_LifeRegenUpgrade);
	AddButton(m_LifeStealChanceUpgrade);
	AddButton(m_LifeStealAmountUpgrade);

	//add actions
	m_MaxHealthUpgrade->OnButtonSelected.BindDynamic(this, &ThisClass::UpgradeButtonsAction);
	m_LifeRegenUpgrade->OnButtonSelected.BindDynamic(this, &ThisClass::UpgradeButtonsAction);
	m_LifeStealChanceUpgrade->OnButtonSelected.BindDynamic(this, &ThisClass::UpgradeButtonsAction);
	m_LifeStealAmountUpgrade->OnButtonSelected.BindDynamic(this, &ThisClass::UpgradeButtonsAction);

	//initialize button
	m_MaxHealthUpgrade->UpdateButton();
	m_LifeRegenUpgrade->UpdateButton();
	m_LifeStealChanceUpgrade->UpdateButton();
	m_LifeStealAmountUpgrade->UpdateButton();


	ActivateWidget();
}

void UHealthUpgradesWidget::UpgradeButtonsAction(USimpleButtonWidget* UpgradeButton)
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
	UpgradeSlot->UpgradeData.GetDefaultObject()->ApplyUpgrade(m_towerWorldManger);
	
	//notify stats changed
	m_towerWorldManger->Notify(UTowerEvent::STATS_CHANGED);
	
	//update button
	UpgradeSlot->UpdateButton();
}

// void UHealthUpgradesWidget::MaxHealthAction(USimpleButtonWidget* button)
// {
// 	bool result = m_MaxHealthUpgrade->TryUpgrade();
// 	if (result)
// 	{
// 		m_towerWorldManger->GetTower()->GetHud()->PushNotification(FText::FromString("Max health increased!!!"), 2.f);
// 		m_towerWorldManger->IncreaseMaxTowerHealth(1);
// 		m_towerWorldManger->Notify(UTowerEvent::STATS_CHANGED);
// 	}
// 	m_MaxHealthUpgrade->UpdateButton();
// }

// void UHealthUpgradesWidget::LifeRegenAction(USimpleButtonWidget* button)
// {
// 	bool result = m_LifeRegenUpgrade->TryUpgrade();
// 	if (result)
// 	{
// 		m_towerWorldManger->GetTower()->GetHud()->PushNotification(FText::FromString("Daily regeneration increased!!!"), 2.f);
// 		m_towerWorldManger->AddRegenPerDay(1);
// 		m_towerWorldManger->Notify(UTowerEvent::STATS_CHANGED);
// 	}
// 	m_LifeRegenUpgrade->UpdateButton();
// }
//
// void UHealthUpgradesWidget::LifeStealChanceAction(USimpleButtonWidget* button)
// {
// 	bool result = m_LifeStealChanceUpgrade->TryUpgrade();
// 	if (result)
// 	{
// 		m_towerWorldManger->GetTower()->GetHud()->PushNotification(FText::FromString("Life steal chance increased!!!"), 2.f);
// 		m_towerWorldManger->AddLifeStealChance(2);
// 		m_towerWorldManger->Notify(UTowerEvent::STATS_CHANGED);
// 	}
// 	m_LifeStealChanceUpgrade->UpdateButton();
// }
//
// void UHealthUpgradesWidget::LifeStealAmountAction(USimpleButtonWidget* button)
// {
// 	bool result = m_LifeStealAmountUpgrade->TryUpgrade();
// 	if (result)
// 	{
// 		m_towerWorldManger->GetTower()->GetHud()->PushNotification(FText::FromString("Life steal amount increased!!!"), 2.f);
// 		m_towerWorldManger->AddLifeStealChance(1);
// 		m_towerWorldManger->Notify(UTowerEvent::STATS_CHANGED);
// 	}
// 	m_LifeStealAmountUpgrade->UpdateButton();
// }

void UHealthUpgradesWidget::ForceUpdateColors()
{
	for (USimpleButtonWidget*& button : m_buttons)
	{
		button->ForceUpdateColors();
	}
}
