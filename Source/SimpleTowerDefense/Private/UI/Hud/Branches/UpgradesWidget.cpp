// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Hud/Branches/UpgradesWidget.h"
#include "UI/Hud/Branches/UpgradeSlotWidget.h"

#include "UI/Hud/Branches/UpgradeData.h"

void UUpgradesWidget::Hide()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

void UUpgradesWidget::Show()
{
	SetVisibility(ESlateVisibility::Visible);
	ForceUpdateColors();
}

void UUpgradesWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	for (TSubclassOf<UUpgradeData> upgrade : UpgradesList)
	{
		UUpgradeSlotWidget* widget = GetUpgradeSlotWidget(upgrade);
	}

	//activate widget
	ActivateWidget();
}

void UUpgradesWidget::UpgradeButtonsAction(USimpleButtonWidget* UpgradeButton)
{
	UUpgradeSlotWidget* UpgradeSlot = Cast<UUpgradeSlotWidget>(UpgradeButton);

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

void UUpgradesWidget::ForceUpdateColors()
{
	for (USimpleButtonWidget*& button : m_buttons)
	{
		button->ForceUpdateColors();
	}
}

UUpgradeSlotWidget* UUpgradesWidget::GetUpgradeSlotWidget(TSubclassOf<UUpgradeData> data)
{
	//create a new widget
	UUpgradeSlotWidget* widget = CreateWidget<UUpgradeSlotWidget>(GetWorld(), UpgradeButtonWidgetClass);
	widget->SetUpgradeData(data);
	widget->UpdateButton();

	//events
	widget->OnButtonSelected.BindDynamic(this, &ThisClass::UpgradeButtonsAction);

	//add button to layout
	m_UpgradesPanel->AddChild(widget);
	
	//add to array
	AddButton(widget);
	widget->Show();

	return widget;
}
