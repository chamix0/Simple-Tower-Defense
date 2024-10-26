// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/TimeManager.h"

#include "Settings/GameSettings.h"


// Sets default values
ATimeManager::ATimeManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATimeManager::BeginPlay()
{
	Super::BeginPlay();
	//get tower world manager
	m_towerWorldManager = GetWorld()->GetSubsystem<UTowerWorldManager>();
	m_dayStopwatch.Start();
}

// Called every frame
void ATimeManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//feed the timer
	m_dayStopwatch.ReceiveTick(DeltaTime);

	//see if its half day
	if (m_dayStopwatch.GetElapsedSeconds() > GetDefault<UGameSettings>()->DayLength / 2.f && !halfDayReached)
	{
		halfDayReached = true;
		m_towerWorldManager->StartNight();
	}

	if (m_dayStopwatch.GetElapsedSeconds() > GetDefault<UGameSettings>()->DayLength)
	{
		//start day
		m_towerWorldManager->StartDay();
		//reset values
		halfDayReached = false;
		//restart timer
		m_dayStopwatch.ReStart();
	}
}
