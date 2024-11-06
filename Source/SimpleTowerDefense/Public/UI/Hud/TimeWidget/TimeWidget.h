// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Basics/HealthBar.h"
#include "TimeWidget.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLETOWERDEFENSE_API UTimeWidget : public UHealthBar
{
	GENERATED_BODY()

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
