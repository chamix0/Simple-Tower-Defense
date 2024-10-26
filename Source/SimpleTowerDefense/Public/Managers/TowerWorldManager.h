﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game_Entities/Enemies/EnemyPool/EnemyPool.h"
#include "ObserverPattern/Publisher.h"
#include "Subsystems/WorldSubsystem.h"
#include "TowerWorldManager.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLETOWERDEFENSE_API UTowerWorldManager : public UWorldSubsystem, public Publisher
{
	GENERATED_BODY()
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

private:
	bool m_isDay = true;
	int m_numDays;
	UPROPERTY()
	FEnemyPool m_enemyPool;

public:
	bool GetIsDay() const;
	void StartNight();
	void StartDay();
	int GetNumDays();
	void AddDay();
	FEnemyPool& GetEnemyPool();
};
