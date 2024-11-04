// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DayNightWidget.h"
#include "Components/Image.h"
#include "SimpleBackground.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLETOWERDEFENSE_API USimpleBackground : public UDayNightWidget
{
	GENERATED_BODY()
	UPROPERTY(meta=(BindWidget))
	UImage* m_background = nullptr;

private:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
