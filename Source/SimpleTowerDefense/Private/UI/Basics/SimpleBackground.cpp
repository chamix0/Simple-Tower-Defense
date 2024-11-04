// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Basics/SimpleBackground.h"

void USimpleBackground::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	m_background->SetColorAndOpacity(m_currentColor);
}
