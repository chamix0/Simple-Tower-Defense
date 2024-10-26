// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SimpleEnemy.h"
#include "Game_Entities/SimpleDayNightActor.h"
#include "Utils/StopWatch.h"
#include "EnemySpawner.generated.h"

UCLASS()
class SIMPLETOWERDEFENSE_API AEnemySpawner : public ASimpleDayNightActor
{
	GENERATED_BODY()


	FStopWatch m_timer;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ASimpleEnemy> m_enemyTemplate;
	UPROPERTY(EditAnywhere)
	float m_spawnRadius = 100;
	UPROPERTY(EditAnywhere)
	float m_spawnCooldown = 1;
	UPROPERTY(EditAnywhere)
	float m_simultaneousSpawns = 1;

public:
	// Sets default values for this actor's properties
	AEnemySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SpawnEnemy();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
