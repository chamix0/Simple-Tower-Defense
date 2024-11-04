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
	/*Day cycle*/
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "General",
		meta = (DisplayName = "Time of a day in seconds"))
	float DayLength = 10.f;
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "General",
	meta = (DisplayName = "ColorChangeSpeed"))
	float ColorChangeSpeed = 5.f;

	/*Enemies*/
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Enemies", meta = (DisplayName = "Max enemy health"))
	int MaxEnemyHealth = 20.f;
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Enemies", meta = (DisplayName = "Max enemy speed"))
	int MaxEnemySpeed = 20.f;
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Enemies", meta = (DisplayName = "Min enemy speed"))
	int MinEnemySpeed = 20.f;
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Enemies", meta = (DisplayName = "Max enemy Scale"))
	float MaxEnemyScale = 0.5f;

	/*tower*/
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tower", meta = (DisplayName = "Initial tower range"))
	float InitialTowerRange = 200.f;
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tower",
		meta = (DisplayName = "Initial Bullets speed"))
	float InitialBulletSpeed = 100.f;
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tower",
		meta = (DisplayName = "Initial Shoots per second"))
	float InitialShootsPerSecond = 1.f;
	UGameSettings();
};
