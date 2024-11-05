﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleTowerDefense/Public/Managers/TowerWorldManager.h"

#include "Game_Entities/Tower/Tower.h"
#include "Kismet/GameplayStatics.h"
#include "Settings/GameSettings.h"
#include "UI/Hud/HudWidget.h"
#include "Utils/MyDebugUtils.h"

void UTowerWorldManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	//initialize tower attributes
	m_range = GetDefault<UGameSettings>()->InitialTowerRange;
	m_bulletsSpeed = GetDefault<UGameSettings>()->InitialBulletSpeed;
	m_ShootsPerSecond = GetDefault<UGameSettings>()->InitialShootsPerSecond;
	m_maxTowerHealth = GetDefault<UGameSettings>()->InitialMaxHealthRange;
}

void UTowerWorldManager::Deinitialize()
{
	Super::Deinitialize();
}

bool UTowerWorldManager::GetIsDay() const
{
	return m_isDay;
}

void UTowerWorldManager::StartNight()
{
	m_isDay = false;
	//notify observers that is night
	Notify(UTowerEvent::IS_NIGHT);
	FString aux = "Starting night: " + FString::FromInt(m_numDays);
	MyDebugUtils::Print(aux);
}

void UTowerWorldManager::StartDay()
{
	m_isDay = true;
	AddDay();
	//notify observers that is day
	Notify(UTowerEvent::IS_DAY);
	FString aux = "Starting day: " + FString::FromInt(m_numDays);
	MyDebugUtils::Print(aux);
}

int UTowerWorldManager::GetNumDays()
{
	return m_numDays;
}

void UTowerWorldManager::AddDay()
{
	m_numDays++;
	m_tower->GetHud()->SetDays(m_numDays);
	//maybe call a ui notification
}

void UTowerWorldManager::BroadCastNotification(UTowerEvent towerEvent)
{
	Notify(towerEvent);
}

FEnemyPool& UTowerWorldManager::GetEnemyPool()
{
	return m_enemyPool;
}

FBulletPool& UTowerWorldManager::GetBulletPool()
{
	return m_bulletPool;
}

float UTowerWorldManager::GetTowerRange() const
{
	return m_range;
}

float UTowerWorldManager::GetBulletsSpeed() const
{
	return m_bulletsSpeed;
}

float UTowerWorldManager::GetShootsPerSecond() const
{
	return m_ShootsPerSecond;
}

int UTowerWorldManager::GetMaxTowerHealth() const
{
	return m_maxTowerHealth;
}

void UTowerWorldManager::IncreaseMaxTowerHealth(int amount)
{
	m_maxTowerHealth += amount;
}

void UTowerWorldManager::SetTower(ATower* tower)
{
	m_tower = tower;
}

int UTowerWorldManager::GetPoints() const
{
	return m_points;
}

void UTowerWorldManager::AddPoints(int amount)
{
	m_points += amount;
	m_tower->GetHud()->SetPoints(m_points);
}

bool UTowerWorldManager::RemovePoints(int amount)
{
	bool canSubtract = m_points - amount >= 0;
	if (canSubtract)
	{
		m_points -= amount;
	}
	m_tower->GetHud()->SetPoints(m_points);
	return canSubtract;
}

ATower* UTowerWorldManager::GetTower() const
{
	return m_tower;
}

bool UTowerWorldManager::GetPaused() const
{
	return m_paused;
}

void UTowerWorldManager::SetPaused(bool value)
{
	m_paused = value;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetPause(m_paused);
}
