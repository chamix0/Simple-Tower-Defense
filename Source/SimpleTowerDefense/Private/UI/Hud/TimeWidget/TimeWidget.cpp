// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Hud/TimeWidget/TimeWidget.h"

#include "Managers/TimeManager.h"
#include "Settings/GameSettings.h"

void UTimeWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	SetValue(GetDefault<UGameSettings>()->DayLength - m_towerWorldManager->GetTimeManager()->GetCurrentTime(),
	         GetDefault<UGameSettings>()->DayLength);
}
