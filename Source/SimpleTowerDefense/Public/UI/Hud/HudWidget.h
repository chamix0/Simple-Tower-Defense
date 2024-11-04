// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "Components/Image.h"
#include "UI/Basics/DayNightWidget.h"
#include "UI/Basics/HealthBar.h"
#include "UI/Basics/SimpleBackground.h"
#include "UI/Basics/SimpleButtonWidget.h"
#include "UI/Basics/SimpleTextWidget.h"
#include "HudWidget.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLETOWERDEFENSE_API UHudWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()
	UPROPERTY()
	UTowerWorldManager* m_towerWorldManager = nullptr;
	UPROPERTY(meta=(BindWidget))
	UHealthBar* m_healthBar = nullptr;
	UPROPERTY(meta=(BindWidget))
	USimpleBackground* m_UpperBarBackground = nullptr;
	UPROPERTY(meta=(BindWidget))
	USimpleTextWidget* m_daysCount = nullptr;
	UPROPERTY(meta=(BindWidget))
	USimpleTextWidget* m_pointsCount = nullptr;
	UPROPERTY(meta=(BindWidget))
	USimpleButtonWidget* m_pauseButton = nullptr;

public:
	virtual void NativeOnInitialized() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	void UpdateHealth(float currentHealth, float maxHealth);
	void SetDays(int num);
	void SetPoints(int num);
	UFUNCTION(BlueprintCallable)
	void PauseAction();
};
