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
	void RangeAction();
	UFUNCTION()
	void ShootsPerSecondAction();
	UFUNCTION()
	void DamageAction();
	UFUNCTION()
	void ShootSpeedAction();
	UFUNCTION()
	void CriticalChanceAction();
	UFUNCTION()
	void CriticalMultiplierAction();
	UFUNCTION()
	void numTargetsAction();
};
