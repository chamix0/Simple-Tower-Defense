// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Hud/Crosshair/CrosshairWidget.h"

void UCrosshairWidget::SetColor(FLinearColor color)
{
	m_crosshairImage->SetColorAndOpacity(color);
}
