// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Basics/SimpleButtonWidget.h"
#include "UpgradeSlotWidget.generated.h"

class UUpgradeData;
/**
 * 
 */
UCLASS()
class SIMPLETOWERDEFENSE_API UUpgradeSlotWidget : public USimpleButtonWidget
{
	GENERATED_BODY()

public:
	//parameters
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUpgradeData> m_UpgradeData;

private:
	UPROPERTY(meta=(BindWidget))
	USimpleTextWidget* m_priceText = nullptr;

	UPROPERTY(meta=(BindWidget))
	USimpleTextWidget* m_progressText = nullptr;

	//values
	int m_numUpgrades = 0;
	bool m_unlocked = false;
	virtual void update(const UTowerEvent event) override;

public:
void SetUpgradeData(TSubclassOf<UUpgradeData> UpgradeData);
	void UpdateUpgradeName();
	virtual void NativeOnInitialized() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void SetHighLight(bool highlighted) override;
	virtual void SetMouseHighLight(bool MouseHighlight) override;
	bool GetIsUnlocked() const;
	void UpdateButton();
	bool TryUpgrade();
};
