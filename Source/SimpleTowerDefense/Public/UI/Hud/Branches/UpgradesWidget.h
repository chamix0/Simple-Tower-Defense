// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Basics/JustButtonsScreen.h"
#include "UpgradesWidget.generated.h"

class UUpgradeData;
/**
 * 
 */
UCLASS()
class SIMPLETOWERDEFENSE_API UUpgradesWidget : public UJustButtonsScreen
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UUpgradeData>> UpgradesList;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUpgradeData> UpgradeButtonWidgetClass;

	UPROPERTY(meta=(BindWidget))
	UUpgradeSlotWidget* m_DailyPointsUpgrade = nullptr;
	UPROPERTY(meta=(BindWidget))
	UUpgradeSlotWidget* m_KillPointsMultiplierUpgrade = nullptr;
	UPROPERTY(meta=(BindWidget))
	UUpgradeSlotWidget* m_MaxPointsUpgrade = nullptr;
	UPROPERTY(meta=(BindWidget))
	UUpgradeSlotWidget* m_MaxGameSpeedUpgrade = nullptr;

public:
	void Hide();
	void Show();
	virtual void NativeOnInitialized() override;

	/*actions*/
	UFUNCTION()
	void UpgradeButtonsAction(USimpleButtonWidget* UpgradeButton);

	void ForceUpdateColors();
};
