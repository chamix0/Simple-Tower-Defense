// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleTowerDefense/Public/Managers/TowerWorldManager.h"

#include "Settings/GameSettings.h"
#include "Utils/MyDebugUtils.h"

void UTowerWorldManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	//initialize tower attributes
	m_range = GetDefault<UGameSettings>()->InitialTowerRange;
	m_bulletsSpeed = GetDefault<UGameSettings>()->InitialBulletSpeed;
	m_ShootsPerSecond = GetDefault<UGameSettings>()->InitialShootsPerSecond;
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
