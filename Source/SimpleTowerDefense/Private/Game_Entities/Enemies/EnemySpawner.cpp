// Fill out your copyright notice in the Description page of Project Settings.


#include "Game_Entities/Enemies/EnemySpawner.h"

#include "Managers/TowerWorldManager.h"
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

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//feed the timer
	m_timer.ReceiveTick(DeltaTime);

	//spawn
	if (m_timer.GetElapsedSeconds() > m_spawnCooldown)
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
