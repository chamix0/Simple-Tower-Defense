// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Basics/SimpleButtonWidget.h"
#include "UpgradeSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLETOWERDEFENSE_API UUpgradeSlotWidget : public USimpleButtonWidget
{
	GENERATED_BODY()

	//parameters
	UPROPERTY(EditAnywhere)
	int baseCost = 0;
	UPROPERTY(EditAnywhere)
	int CostIncrement = 0;
	UPROPERTY(EditAnywhere)
	int unlockDay = 1;
	/*-1 means no limit other, is the limit*/
	UPROPERTY(EditAnywhere)
	int MaxUpgrades = -1;
	UPROPERTY(meta=(BindWidget))
	USimpleTextWidget* m_priceText = nullptr;

	UPROPERTY(meta=(BindWidget))
	USimpleTextWidget* m_progressText = nullptr;

	//values
	int m_numUpgrades = 0;
	bool m_unlocked = false;
	virtual void update(const UTowerEvent event) override;

public:
	virtual void NativeOnInitialized() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void SetHighLight(bool highlighted) override;
	virtual void SetMouseHighLight(bool MouseHighlight) override;
	bool GetIsUnlocked() const;
	void UpdateButton();
	bool TryUpgrade();
};
