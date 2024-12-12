// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EnemyPool.generated.h"

/**
 * 
 */

class ASimpleEnemy;

USTRUCT()
struct FEnemyPool
{
	GENERATED_BODY()

	FEnemyPool();

	UPROPERTY()
	TArray<ASimpleEnemy*> m_AvailibleEnemies;
	UPROPERTY()
	TArray<ASimpleEnemy*> m_ActiveEnemies;
	
	ASimpleEnemy* GetEnemy(UWorld* world, TSubclassOf<AActor> templateEnemy);
	ASimpleEnemy* FindEnemy();
	void InsertEnemyToPool(ASimpleEnemy* enemy);
};
