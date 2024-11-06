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
		meta = (DisplayName = "Color Change Speed"))
	float ColorChangeSpeed = 5.f;
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "General",
		meta = (DisplayName = "Color Change Speed UI"))
	float ColorChangeSpeedUI = 5.f;
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tower",
		meta = (DisplayName = "game speed increment"))
	float GameSpeedIncrement = 0.1f;
	/*Enemies*/
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Enemies", meta = (DisplayName = "Max enemy health"))
	int MaxEnemyHealth = 20.f;
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Enemies", meta = (DisplayName = "Max enemy speed"))
	int MaxEnemySpeed = 20.f;
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Enemies", meta = (DisplayName = "Min enemy speed"))
	int MinEnemySpeed = 20.f;
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Enemies", meta = (DisplayName = "Max enemy Scale"))
	float MaxEnemyScale = 0.5f;
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Enemies",
		meta = (DisplayName = "Simultaneous Spawn Increment"))
	float SimultaneousSpawnIncrement = 0.3f;
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Enemies",
		meta = (DisplayName = "Spawns Per Second Increment"))
	float SpawnsPerSecondIncrement = 0.1f;
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Enemies",
		meta = (DisplayName = "Difficulty Increment"))
	float DifficultyIncrement = 0.25f;
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Enemies",
		meta = (DisplayName = "Enemy Out Of Range Speed"))
	float EnemyOutOfRangeSpeed = 100.f;

	/*tower*/
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tower",
		meta = (DisplayName = "Initial tower max health"))
	int InitialMaxHealthRange = 50;
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tower", meta = (DisplayName = "Initial tower range"))
	float InitialTowerRange = 200.f;
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tower",
		meta = (DisplayName = "Initial Bullets speed"))
	float InitialBulletSpeed = 100.f;
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tower",
		meta = (DisplayName = "Initial Shoots per second"))
	float InitialShootsPerSecond = 1.f;
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tower",
		meta = (DisplayName = "Initial Damage"))
	float InitialDamage = 1;


	//upgrades
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tower",
		meta = (DisplayName = "Tower Range Upgrade Increment"))
	float TowerRangeUpgradeIncrement = 25.f;
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tower",
		meta = (DisplayName = "Shoots per second Upgrade Increment"))
	float ShootsPerSecondUpgradeIncrement = 0.1f;
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tower",
		meta = (DisplayName = "damage Upgrade Increment"))
	float DamageUpgradeIncrement = 0.5f;
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tower",
		meta = (DisplayName = "Bullet speed Upgrade Increment"))
	float BulletsSpeedIncrement = 10.f;
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tower",
		meta = (DisplayName = "Critical chance Upgrade Increment"))
	int CriticalChanceIncrement = 1;
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tower",
		meta = (DisplayName = "critical multiplier Upgrade Increment"))
	float CriticalMultiplierIncrement = 0.1f;
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tower",
		meta = (DisplayName = "daily points increment"))
	int DailyPointsIncrement = 5;
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tower",
		meta = (DisplayName = "kill points multiplier increment"))
	float KillPointsMultiplierIncrement = 0.1;

	UGameSettings();
};
