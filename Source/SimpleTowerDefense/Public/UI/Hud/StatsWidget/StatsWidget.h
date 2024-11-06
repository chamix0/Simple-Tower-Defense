// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Basics/DayNightWidget.h"
#include "UI/Basics/SimpleTextWidget.h"
#include "StatsWidget.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLETOWERDEFENSE_API UStatsWidget : public UDayNightWidget
{
	GENERATED_BODY()

	UPROPERTY(meta=(BindWidget))
	UTextBlock* m_textWidget = nullptr;

private:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	FString GetStatsText();
	virtual void update(const UTowerEvent event) override;
};
