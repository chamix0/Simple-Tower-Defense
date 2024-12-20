// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game_Entities/Enemies/EnemyPool/EnemyPool.h"
#include "Game_Entities/Tower/Bullets/BulletPool.h"
#include "ObserverPattern/Publisher.h"
#include "Subsystems/WorldSubsystem.h"
#include "TowerWorldManager.generated.h"

class ATimeManager;
class ATower;
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
	bool m_paused = false;
	bool m_isDay = true;
	int m_numDays = 0;
	int m_points = 0;
	


	UPROPERTY()
	FEnemyPool m_enemyPool;
	FBulletPool m_bulletPool;

	UPROPERTY()
	ATower* m_tower = nullptr;
	UPROPERTY()
	ATimeManager* m_TimeManager = nullptr;

	/* Tower attributes */
	//health attributes
	UPROPERTY()
	int m_maxTowerHealth = 100;
	UPROPERTY()
	int m_regenPerDay = 0;
	UPROPERTY()
	int m_lifeStealChance = 0;
	UPROPERTY()
	int m_lifeStealAmmount = 1;

	//damage attributes
	UPROPERTY()
	float m_range = 200.f;
	UPROPERTY()
	float m_bulletsSpeed = 10.f;
	UPROPERTY()
	float m_ShootsPerSecond = 1.f;
	UPROPERTY()
	float m_Damage = 1.f;
	UPROPERTY()
	int m_criticalChance = 0;
	UPROPERTY()
	float m_criticalMultiplier = 1;

	//points attiributes
	UPROPERTY()
	float m_MaxTimeScale = 1.1f;
	UPROPERTY()
	float m_killPointMultiplier = 1.f;
	UPROPERTY()
	int m_DailyPoints = 0;
	UPROPERTY()
	int m_maxPoints = 1000;

public:
	bool GetIsDay() const;
	void StartNight();
	void StartDay();
	int GetNumDays();
	void AddDay();
	void BroadCastNotification(UTowerEvent towerEvent);
	FEnemyPool& GetEnemyPool();
	FBulletPool& GetBulletPool();

	//range
	float GetTowerRange() const;
	void IncreaseTowerRange(float amount);

	//damage
	float GetDamage() const;
	void IncreaseDamage(float amount);

	//bullets speed
	float GetBulletsSpeed() const;
	void IncreaseBulletsSpeed(float value);

	//shoots per second
	float GetShootsPerSecond() const;
	void IncreaseShootsPerSecond(float value);

	//critical damage
	int GetCriticalChance() const;
	void IncreaseCriticalChance(int value);
	float GetCriticalMultiplier() const;
	void IncreaseCriticalMultiplier(float value);

	//time scale
	float GetMaxTimeScale() const;
	void IncrementTimeScale(float amount);

	//kill point multiplier
	float GetKillPointMultiplier() const;
	void IncrementKillPointMultiplier(float amount);

	//daily points
	int GetDailyPoints() const;
	void IncrementDailyPoints(int amount);

	//max Points
	void IncrementMaxPoints(int amount);


	int GetMaxTowerHealth() const;
	void IncreaseMaxTowerHealth(int amount);
	void SetTower(ATower* tower);
	int GetPoints() const;
	void AddPoints(int amount);
	bool RemovePoints(int amount);
	ATower* GetTower() const;
	bool GetPaused() const;
	void SetPaused(bool value);
	int GetRegenPerDay() const;
	void AddRegenPerDay(int amount);
	int GetLifeStealChance() const;
	int GetLifeStealAmount() const;
	void AddLifeStealChance(int value);
	void AddLifeStealAmount(int value);
	//time manager
	ATimeManager* GetTimeManager() const;
	void SetTimeManager(ATimeManager* timeManager) ;

};
