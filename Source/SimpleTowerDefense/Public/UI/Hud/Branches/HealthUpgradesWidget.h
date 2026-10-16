// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UpgradeSlotWidget.h"
#include "UI/Basics/JustButtonsScreen.h"
#include "Game_Entities/Tower/Tower.h"
#include "HealthUpgradesWidget.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLETOWERDEFENSE_API UHealthUpgradesWidget : public UJustButtonsScreen
{
	GENERATED_BODY()

	UPROPERTY(meta=(BindWidget))
	UUpgradeSlotWidget* m_MaxHealthUpgrade = nullptr;

	UPROPERTY(meta=(BindWidget))
	UUpgradeSlotWidget* m_LifeRegenUpgrade = nullptr;

	UPROPERTY(meta=(BindWidget))
	UUpgradeSlotWidget* m_LifeStealChanceUpgrade = nullptr;

	UPROPERTY(meta=(BindWidget))
	UUpgradeSlotWidget* m_LifeStealAmountUpgrade = nullptr;

public:
	void Hide();
	void Show();
	virtual void NativeOnInitialized() override;

	/*actions*/
	UFUNCTION()
	void UpgradeButtonsAction(USimpleButtonWidget* UpgradeButton);

	// UFUNCTION()
	// void MaxHealthAction(USimpleButtonWidget* button);
	// UFUNCTION()
	// void LifeRegenAction(USimpleButtonWidget* button);
	// UFUNCTION()
	// void LifeStealChanceAction(USimpleButtonWidget* button);
	// UFUNCTION()
	// void LifeStealAmountAction(USimpleButtonWidget* button);
	void ForceUpdateColors();
};
