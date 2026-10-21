// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Basics/JustButtonsScreen.h"
#include "UpgradesWidget.generated.h"

class UUpgradeSlotWidget;
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
	TSubclassOf<UUpgradeSlotWidget> UpgradeButtonWidgetClass;

	UPROPERTY(meta=(BindWidget))
	UPanelWidget* m_UpgradesPanel;

public:
	void Hide();
	void Show();
	virtual void NativeOnInitialized() override;

	/*actions*/
	UFUNCTION()
	void UpgradeButtonsAction(USimpleButtonWidget* UpgradeButton);

	void ForceUpdateColors();

private:
	UUpgradeSlotWidget* GetUpgradeSlotWidget(TSubclassOf<UUpgradeData> data);
};
