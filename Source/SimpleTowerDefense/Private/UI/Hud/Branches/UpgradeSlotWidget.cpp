// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Hud/Branches/UpgradeSlotWidget.h"

#include "Game_Entities/Tower/Tower.h"
#include "UI/Hud/HudWidget.h"


void UUpgradeSlotWidget::update(const UTowerEvent event)
{
	Super::update(event);

	if (event == UTowerEvent::IS_DAY)
	{
		m_unlocked = m_TowerWorldManager->GetNumDays() >= unlockDay;
		UpdateButton();
	}
	//update just in case
	UpdateButton();
}

void UUpgradeSlotWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	m_priceText->SetDayColor(m_nightColor);
	m_priceText->SetNightColor(m_dayColor);
	m_progressText->SetDayColor(m_nightColor);
	m_progressText->SetNightColor(m_dayColor);
}

void UUpgradeSlotWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UUpgradeSlotWidget::SetHighLight(bool highlighted)
{
	Super::SetHighLight(highlighted);
	m_progressText->SetHighlighted(highlighted || m_mouseHighlight);
	m_priceText->SetHighlighted(highlighted || m_mouseHighlight);
	UpdateButton();
}

void UUpgradeSlotWidget::SetMouseHighLight(bool MouseHighlight)
{
	Super::SetMouseHighLight(MouseHighlight);
	UpdateButton();
}

bool UUpgradeSlotWidget::GetIsUnlocked() const
{
	return m_unlocked;
}

void UUpgradeSlotWidget::UpdateButton()
{
	int prize = baseCost + CostIncrement * m_numUpgrades;
	bool highlighted = m_highlighted || m_mouseHighlight;
	/*progress text*/
	//possible cases
	bool soldOut = m_numUpgrades >= MaxUpgrades;
	bool notEnoughPoints = m_TowerWorldManager->GetPoints() < prize;

	if (m_unlocked)
	{
		if (soldOut)
		{
			m_priceText->SetTextDirectly(FText::FromString("MAX UPGRADES"), highlighted);
		}
		else if (notEnoughPoints)
		{
			m_priceText->SetTextDirectly(FText::FromString("Not Enought \n(" + FString::FromInt(prize) + " pts)"),
			                             highlighted);
		}
		else
		{
			m_priceText->SetTextDirectly(FText::FromString(FString::FromInt(prize) + " pts"), highlighted);
		}
	}
	else
	{
		m_priceText->SetTextDirectly(FText::FromString("Unlocks on day " + FString::FromInt(unlockDay)), highlighted);
	}

	/*PROGRESS TEXT*/
	m_progressText->SetTextDirectly(
		FText::FromString(FString::FromInt(m_numUpgrades) + "/" + FString::FromInt(MaxUpgrades)), highlighted);
}

bool UUpgradeSlotWidget::TryUpgrade()
{
	int prize = baseCost + CostIncrement * m_numUpgrades;

	//locked
	if (!m_unlocked)
	{
		m_TowerWorldManager->GetTower()->GetHud()->PushNotification("this Upgrade is still locked",2.f);
		return false;
	}

	//sold out
	if (m_numUpgrades >= MaxUpgrades)
	{
		m_TowerWorldManager->GetTower()->GetHud()->PushNotification("Upgrade limit reached...",2.f);
		return false;
	}

	bool result = m_TowerWorldManager->RemovePoints(prize);
	if (result)
	{
		m_numUpgrades++;
	}

	return result;
}
