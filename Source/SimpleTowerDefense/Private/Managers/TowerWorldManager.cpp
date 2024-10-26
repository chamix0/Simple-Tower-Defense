// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleTowerDefense/Public/Managers/TowerWorldManager.h"

#include "Utils/MyDebugUtils.h"

void UTowerWorldManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
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

FEnemyPool& UTowerWorldManager::GetEnemyPool() 
{
	return m_enemyPool;
}
