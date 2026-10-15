// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Hud/Branches/DamageUpgradesWidget.h"

#include "Game_Entities/Tower/Tower.h"
#include "Settings/GameSettings.h"
#include "UI/Hud/HudWidget.h"
#include "UI/Hud/Branches/UpgradeData.h"

void UDamageUpgradesWidget::Hide()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

void UDamageUpgradesWidget::Show()
{
	SetVisibility(ESlateVisibility::Visible);
	ForceUpdateColors();
}

void UDamageUpgradesWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	//add buttons
	AddButton(m_RangeUpgrade);
	AddButton(m_ShootsPerSecondUpgrade);
	AddButton(m_DamageUpgrade);
	AddButton(m_ShootSpeedUpgrade);
	AddButton(m_CriticalChanceUpgrade);
	AddButton(m_CriticalMultiplierUpgrade);
	AddButton(m_numTargetsUpgrade);


	//add actions

	m_RangeUpgrade->OnButtonSelected.BindDynamic(this, &ThisClass::RangeAction);
	m_ShootsPerSecondUpgrade->OnButtonSelected.BindDynamic(this, &ThisClass::ShootsPerSecondAction);
	m_DamageUpgrade->OnButtonSelected.BindDynamic(this, &ThisClass::UpgradeButtonsAction);
	m_ShootSpeedUpgrade->OnButtonSelected.BindDynamic(this, &ThisClass::ShootSpeedAction);
	m_CriticalChanceUpgrade->OnButtonSelected.BindDynamic(this, &ThisClass::CriticalChanceAction);
	m_CriticalMultiplierUpgrade->OnButtonSelected.BindDynamic(this, &ThisClass::CriticalMultiplierAction);
	m_numTargetsUpgrade->OnButtonSelected.BindDynamic(this, &ThisClass::numTargetsAction);

	//initialize button
	m_RangeUpgrade->SetText(FText::FromString("Range"));
	m_RangeUpgrade->UpdateButton();

	m_ShootsPerSecondUpgrade->SetText(FText::FromString("Shoots per second"));
	m_ShootsPerSecondUpgrade->UpdateButton();

	m_DamageUpgrade->SetText(FText::FromString("Damage"));
	m_DamageUpgrade->UpdateButton();

	m_ShootSpeedUpgrade->SetText(FText::FromString("Bullets Speed"));
	m_ShootSpeedUpgrade->UpdateButton();

	m_CriticalChanceUpgrade->SetText(FText::FromString("Critical chance"));
	m_CriticalChanceUpgrade->UpdateButton();

	m_CriticalMultiplierUpgrade->SetText(FText::FromString("Critical Multiplier"));
	m_CriticalMultiplierUpgrade->UpdateButton();

	m_numTargetsUpgrade->SetText(FText::FromString("simultaneous targets"));
	m_numTargetsUpgrade->UpdateButton();


	ActivateWidget();
}

void UDamageUpgradesWidget::UpgradeButtonsAction(USimpleButtonWidget* UpgradeButton)
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

void UDamageUpgradesWidget::RangeAction(USimpleButtonWidget* UpgradeButton)
{
	bool result = m_RangeUpgrade->TryUpgrade();
	if (result)
	{
		m_towerWorldManger->GetTower()->GetHud()->PushNotification(FText::FromString("Range increased!!!"), 2.f);
		m_towerWorldManger->IncreaseTowerRange(GetDefault<UGameSettings>()->TowerRangeUpgradeIncrement);
		m_towerWorldManger->Notify(UTowerEvent::STATS_CHANGED);
	}
	
	// m_RangeUpgrade->UpgradeData->ApplyUpgrade(m_towerWorldManger);
	m_RangeUpgrade->UpdateButton();
}

void UDamageUpgradesWidget::ShootsPerSecondAction(USimpleButtonWidget* UpgradeButton)
{
	bool result = m_ShootsPerSecondUpgrade->TryUpgrade();
	if (result)
	{
		m_towerWorldManger->GetTower()->GetHud()->PushNotification(FText::FromString("Shoots per second increased!!!"), 2.f);
		m_towerWorldManger->IncreaseShootsPerSecond(GetDefault<UGameSettings>()->ShootsPerSecondUpgradeIncrement);
		m_towerWorldManger->Notify(UTowerEvent::STATS_CHANGED);
	}
	m_ShootsPerSecondUpgrade->UpdateButton();
}

// void UDamageUpgradesWidget::DamageAction(USimpleButtonWidget* UpgradeButton)
// {
// 	bool result = m_DamageUpgrade->TryUpgrade();
// 	if (!result)
// 	{
// 		return;
// 		// m_towerWorldManger->GetTower()->GetHud()->PushNotification(FText::FromString("Base damage increased!!!"), 2.f);
// 		// m_towerWorldManger->IncreaseDamage(GetDefault<UGameSettings>()->DamageUpgradeIncrement);
// 		// m_towerWorldManger->Notify(UTowerEvent::STATS_CHANGED);
// 	}
// 	
// 	m_RangeUpgrade->UpgradeData->ApplyUpgrade(m_towerWorldManger);
// 	m_DamageUpgrade->UpdateButton();
// }

void UDamageUpgradesWidget::ShootSpeedAction(USimpleButtonWidget* UpgradeButton)
{
	bool result = m_ShootSpeedUpgrade->TryUpgrade();
	if (result)
	{
		m_towerWorldManger->GetTower()->GetHud()->PushNotification(FText::FromString("Bullets Speed increased!!!"), 2.f);
		m_towerWorldManger->IncreaseBulletsSpeed(GetDefault<UGameSettings>()->BulletsSpeedIncrement);
		m_towerWorldManger->Notify(UTowerEvent::STATS_CHANGED);
	}
	m_ShootSpeedUpgrade->UpdateButton();
}

void UDamageUpgradesWidget::CriticalChanceAction(USimpleButtonWidget* UpgradeButton)
{
	bool result = m_CriticalChanceUpgrade->TryUpgrade();
	if (result)
	{
		m_towerWorldManger->GetTower()->GetHud()->PushNotification(FText::FromString("Critical chance increased!!!"), 2.f);
		m_towerWorldManger->IncreaseCriticalChance(GetDefault<UGameSettings>()->CriticalChanceIncrement);
		m_towerWorldManger->Notify(UTowerEvent::STATS_CHANGED);
	}
	m_CriticalChanceUpgrade->UpdateButton();
}

void UDamageUpgradesWidget::CriticalMultiplierAction(USimpleButtonWidget* UpgradeButton)
{
	bool result = m_CriticalMultiplierUpgrade->TryUpgrade();
	if (result)
	{
		m_towerWorldManger->GetTower()->GetHud()->PushNotification(FText::FromString("Critical multiplier increased!!!"), 2.f);
		m_towerWorldManger->IncreaseCriticalMultiplier(GetDefault<UGameSettings>()->CriticalMultiplierIncrement);
		m_towerWorldManger->Notify(UTowerEvent::STATS_CHANGED);
	}
	m_CriticalMultiplierUpgrade->UpdateButton();
}

void UDamageUpgradesWidget::numTargetsAction(USimpleButtonWidget* UpgradeButton)
{
	bool result = m_numTargetsUpgrade->TryUpgrade();
	if (result)
	{
		m_towerWorldManger->GetTower()->GetHud()->PushNotification(FText::FromString("Num targets increased!!!"), 2.f);
		m_towerWorldManger->GetTower()->AddCrossHair();
		m_towerWorldManger->Notify(UTowerEvent::STATS_CHANGED);
	}
	m_numTargetsUpgrade->UpdateButton();
}

void UDamageUpgradesWidget::ForceUpdateColors()
{
	for (USimpleButtonWidget*& button : m_buttons)
	{
		button->ForceUpdateColors();
	}
}
