// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UpgradeSlotWidget.h"
#include "UI/Basics/JustButtonsScreen.h"
#include "PointsUpgradesWidget.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLETOWERDEFENSE_API UPointsUpgradesWidget : public UJustButtonsScreen
{
	GENERATED_BODY()

	UPROPERTY(meta=(BindWidget))
	UUpgradeSlotWidget* m_DailyPointsUpgrade = nullptr;
	UPROPERTY(meta=(BindWidget))
	UUpgradeSlotWidget* m_KillPointsMultiplierUpgrade = nullptr;
	UPROPERTY(meta=(BindWidget))
	UUpgradeSlotWidget* m_MaxGameSpeedUpgrade = nullptr;

public:
	void Hide();
	void Show();
	virtual void NativeOnInitialized() override;

	/*actions*/
	UFUNCTION()
	void DailyPointsAction();
	UFUNCTION()
	void KillPointMultiplierAction();
	UFUNCTION()
	void MaxGameSpeedAction();
};
