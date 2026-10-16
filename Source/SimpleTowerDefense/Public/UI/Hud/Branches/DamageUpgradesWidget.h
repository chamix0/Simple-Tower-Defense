// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UpgradeSlotWidget.h"
#include "UI/Basics/JustButtonsScreen.h"
#include "DamageUpgradesWidget.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLETOWERDEFENSE_API UDamageUpgradesWidget : public UJustButtonsScreen
{
	GENERATED_BODY()


	UPROPERTY(meta=(BindWidget))
	UUpgradeSlotWidget* m_RangeUpgrade = nullptr;
	UPROPERTY(meta=(BindWidget))
	UUpgradeSlotWidget* m_ShootsPerSecondUpgrade = nullptr;
	UPROPERTY(meta=(BindWidget))
	UUpgradeSlotWidget* m_DamageUpgrade = nullptr;
	UPROPERTY(meta=(BindWidget))
	UUpgradeSlotWidget* m_ShootSpeedUpgrade = nullptr;
	UPROPERTY(meta=(BindWidget))
	UUpgradeSlotWidget* m_CriticalChanceUpgrade = nullptr;
	UPROPERTY(meta=(BindWidget))
	UUpgradeSlotWidget* m_CriticalMultiplierUpgrade = nullptr;
	UPROPERTY(meta=(BindWidget))
	UUpgradeSlotWidget* m_numTargetsUpgrade = nullptr;

public:
	void Hide();
	void Show();
	virtual void NativeOnInitialized() override;

	/*actions*/
	UFUNCTION()
	void UpgradeButtonsAction(USimpleButtonWidget* UpgradeButton);
	
	// UFUNCTION()
	// void RangeAction(USimpleButtonWidget* UpgradeButton);
	// UFUNCTION()
	// void ShootsPerSecondAction(USimpleButtonWidget* UpgradeButton);
	// UFUNCTION()
	// void DamageAction(USimpleButtonWidget* UpgradeButton);
	// UFUNCTION()
	// void ShootSpeedAction(USimpleButtonWidget* UpgradeButton);
	// UFUNCTION()
	// void CriticalChanceAction(USimpleButtonWidget* UpgradeButton);
	// UFUNCTION()
	// void CriticalMultiplierAction(USimpleButtonWidget* UpgradeButton);
	// UFUNCTION()
	// void numTargetsAction(USimpleButtonWidget* UpgradeButton);
	void ForceUpdateColors();
};
