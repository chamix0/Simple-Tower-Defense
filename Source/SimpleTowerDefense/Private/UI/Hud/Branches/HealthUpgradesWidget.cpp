// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Hud/Branches/HealthUpgradesWidget.h"

#include "UI/Hud/HudWidget.h"

void UHealthUpgradesWidget::Hide()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

void UHealthUpgradesWidget::Show()
{
	SetVisibility(ESlateVisibility::Visible);
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
	m_MaxHealthUpgrade->OnButtonSelected.BindDynamic(this, &ThisClass::MaxHealthAction);
	m_LifeRegenUpgrade->OnButtonSelected.BindDynamic(this, &ThisClass::LifeRegenAction);
	m_LifeStealChanceUpgrade->OnButtonSelected.BindDynamic(this, &ThisClass::LifeStealChanceAction);
	m_LifeStealAmountUpgrade->OnButtonSelected.BindDynamic(this, &ThisClass::LifeStealAmountAction);

	//initialize button
	m_MaxHealthUpgrade->SetText(FText::FromString("Max health"));
	m_MaxHealthUpgrade->UpdateButton();
	m_LifeRegenUpgrade->SetText(FText::FromString("Life regen"));
	m_LifeRegenUpgrade->UpdateButton();
	m_LifeStealChanceUpgrade->SetText(FText::FromString("Life steal chance"));
	m_LifeStealChanceUpgrade->UpdateButton();
	m_LifeStealAmountUpgrade->SetText(FText::FromString("Life steal amount"));
	m_LifeStealAmountUpgrade->UpdateButton();


	ActivateWidget();
}

void UHealthUpgradesWidget::MaxHealthAction()
{
	bool result = m_MaxHealthUpgrade->TryUpgrade();
	if (result)
	{
		m_towerWorldManger->GetTower()->GetHud()->PushNotification("Max health increased!!!", 2.f);
		m_towerWorldManger->IncreaseMaxTowerHealth(1);
		m_towerWorldManger->Notify(UTowerEvent::STATS_CHANGED);
	}
	m_MaxHealthUpgrade->UpdateButton();
}

void UHealthUpgradesWidget::LifeRegenAction()
{
	bool result = m_LifeRegenUpgrade->TryUpgrade();
	if (result)
	{
		m_towerWorldManger->GetTower()->GetHud()->PushNotification("Daily regeneration increased!!!", 2.f);
		m_towerWorldManger->AddRegenPerDay(1);
		m_towerWorldManger->Notify(UTowerEvent::STATS_CHANGED);
	}
	m_LifeRegenUpgrade->UpdateButton();
}

void UHealthUpgradesWidget::LifeStealChanceAction()
{
	bool result = m_LifeStealChanceUpgrade->TryUpgrade();
	if (result)
	{
		m_towerWorldManger->GetTower()->GetHud()->PushNotification("Life steal chance increased!!!", 2.f);
		m_towerWorldManger->AddLifeStealChance(2);
		m_towerWorldManger->Notify(UTowerEvent::STATS_CHANGED);
	}
	m_LifeStealChanceUpgrade->UpdateButton();
}

void UHealthUpgradesWidget::LifeStealAmountAction()
{
	bool result = m_LifeStealAmountUpgrade->TryUpgrade();
	if (result)
	{
		m_towerWorldManger->GetTower()->GetHud()->PushNotification("Life steal amount increased!!!", 2.f);
		m_towerWorldManger->AddLifeStealChance(1);
		m_towerWorldManger->Notify(UTowerEvent::STATS_CHANGED);
	}
	m_LifeStealAmountUpgrade->UpdateButton();
}
