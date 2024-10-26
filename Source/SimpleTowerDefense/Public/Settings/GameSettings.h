// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "GameSettings.generated.h"

/**
 * 
 */
UCLASS(Config=Game, defaultconfig, meta = (DisplayName="Game Settings"))
class SIMPLETOWERDEFENSE_API UGameSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "General",meta = (DisplayName = "Time of a day in seconds"))
	float DayLength = 10.f;
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Enemies",meta = (DisplayName = "Max enemy health"))
	int MaxEnemyHealth = 20.f;
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Enemies",meta = (DisplayName = "Max enemy Scale"))
	float MaxEnemyScale = 0.5f;
	
	UGameSettings();
};
