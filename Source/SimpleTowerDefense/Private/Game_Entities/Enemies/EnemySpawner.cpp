// Fill out your copyright notice in the Description page of Project Settings.


#include "Game_Entities/Enemies/EnemySpawner.h"

#include "Managers/TimeManager.h"
#include "Managers/TowerWorldManager.h"
#include "Settings/GameSettings.h"
#include "Utils/MyDebugUtils.h"


// Sets default values
AEnemySpawner::AEnemySpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	//start timer
	m_timer.Start();
}

void AEnemySpawner::SpawnEnemy()
{
	if (m_enemyTemplate != nullptr)
	{
		ASimpleEnemy* Enemy = m_towerWorldManager->GetEnemyPool().GetEnemy(GetWorld(), m_enemyTemplate);
		FVector spawnPoint = FVector(FMath::RandPointInCircle(m_spawnRadius), 0).GetSafeNormal2D() * m_spawnRadius;
		Enemy->InitializeEnemy(spawnPoint);
		return;
	}
	MyDebugUtils::Print("NO ENEMY TEMPLATE GIVEN TO ENEMY SPAWNER!!!", FColor::Red);
}

float AEnemySpawner::GetSpawnLimitator() const
{
	if (!m_towerWorldManager->GetTimeManager())
	{
		return 1;
	}
	float currentTime = m_towerWorldManager->GetTimeManager()->GetCurrentTime();
	float dayLength = GetDefault<UGameSettings>()->DayLength;
	//a cos curve that starts at 0 peacks at half of day and night and then goes down
	return (1 - FMath::Cos(currentTime * (4 * PI / dayLength))) / 2;
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//feed the timer
	m_timer.ReceiveTick(DeltaTime);

	//spawn the most arround middle of the day and middle of the night
	float aux = GetSpawnLimitator();
	if (m_timer.GetElapsedSeconds() > 1 / FMath::Max(0.01f, m_spawnsPerSecond * aux))
	{
		//restart timer
		m_timer.ReStart();

		//spawn enemies
		for (int i = 0; i < m_simultaneousSpawns; ++i)
		{
			SpawnEnemy();
		}
	}
}

void AEnemySpawner::update(const UTowerEvent event)
{
	Super::update(event);
	if (event == UTowerEvent::IS_DAY)
	{
		//simultaneous spawns
		m_simultaneousSpawns += m_towerWorldManager->GetNumDays() * GetDefault<UGameSettings>()->
			SimultaneousSpawnIncrement;
		//spawn cooldown
		m_spawnsPerSecond += m_towerWorldManager->GetNumDays() * GetDefault<UGameSettings>()->SpawnsPerSecondIncrement;
	}
}
