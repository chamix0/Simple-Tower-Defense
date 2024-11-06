// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Basics/DayNightWidget.h"
#include "UI/Basics/SimpleTextWidget.h"
#include "Utils/StopWatch.h"
#include "HudNotificationsWidget.generated.h"

USTRUCT()
struct FPopUpInfo
{
	GENERATED_BODY()

public:
	FPopUpInfo();
	FPopUpInfo(FString _Text, float _time);
	FString text;
	float time;
};

/**
 * 
 */
UCLASS()
class SIMPLETOWERDEFENSE_API UHudNotificationsWidget : public UDayNightWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta=(BindWidget))
	USimpleTextWidget* text = nullptr;

private:
	TArray<FPopUpInfo> textQueue;
	FStopWatch StopWatch;
	FPopUpInfo currentPopUp;

public:
	void PushText(FString textToDisplay, float time);


private:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeOnInitialized() override;
	void ShowNextText();
};
