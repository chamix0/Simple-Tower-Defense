// Fill out your copyright notice in the Description page of Project Settings.


#include "Game_Entities/Enemies/EnemyPool/EnemyPool.h"

#include "Game_Entities/Enemies/SimpleEnemy.h"

FEnemyPool::FEnemyPool()
{
}

ASimpleEnemy* FEnemyPool::GetEnemy(UWorld* world, TSubclassOf<AActor> templateEnemy)
{
	//try get an enemy
	ASimpleEnemy* enemy = FindEnemy();
	if (enemy != nullptr)
	{
		//mark as its not a available
		enemy->SetIsAvailable(false);
		return enemy;
	}

	//no available enemy so create one 
	FActorSpawnParameters SpawnInfo;
	AActor* spawnedActor = world->SpawnActor<AActor>(templateEnemy, FVector(0, 0, -1000), FRotator(), SpawnInfo);

	//add to a folder to make it cleaner on editor
#if WITH_EDITOR
	spawnedActor->SetFolderPath("EnemyPool");
#endif

	enemy = Cast<ASimpleEnemy>(spawnedActor);
	//make the enemy not available
	enemy->SetIsAvailable(false);

	return enemy;
}

ASimpleEnemy* FEnemyPool::FindEnemy()
{
	//create a copy to safely remove elements
	TArray<ASimpleEnemy*> aux = m_AvailibleEnemies;

	for (int i = 0; i < aux.Num(); i++)
	{
		ASimpleEnemy* enemy = aux[i];
		if (enemy->GetIsAvailable())
		{
			//remove available enemy from array
			m_AvailibleEnemies.Remove(enemy);

			//return enemy
			return enemy;
		}
	}
	return nullptr;
}

void FEnemyPool::InsertEnemyToPool(ASimpleEnemy* enemy)
{
	m_AvailibleEnemies.AddUnique(enemy);
}
