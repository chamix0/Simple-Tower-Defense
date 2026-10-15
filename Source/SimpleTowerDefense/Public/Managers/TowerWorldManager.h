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
	UFUNCTION(BlueprintCallable)
	bool GetIsDay() const;
	UFUNCTION(BlueprintCallable)
	void StartNight();
	UFUNCTION(BlueprintCallable)
	void StartDay();
	UFUNCTION(BlueprintCallable)
	int GetNumDays();
	UFUNCTION(BlueprintCallable)
	void AddDay();
	UFUNCTION(BlueprintCallable)
	void BroadCastNotification(UTowerEvent towerEvent);
	UFUNCTION()
	FEnemyPool& GetEnemyPool();
	UFUNCTION()
	FBulletPool& GetBulletPool();

	//range
	UFUNCTION(BlueprintCallable)
	float GetTowerRange() const;
	UFUNCTION(BlueprintCallable)
	void IncreaseTowerRange(float amount);

	//damage
	UFUNCTION(BlueprintCallable)
	float GetDamage() const;
	UFUNCTION(BlueprintCallable)
	void IncreaseDamage(float amount);

	//bullets speed
	UFUNCTION(BlueprintCallable)
	float GetBulletsSpeed() const;
	UFUNCTION(BlueprintCallable)
	void IncreaseBulletsSpeed(float value);

	//shoots per second
	UFUNCTION(BlueprintCallable)
	float GetShootsPerSecond() const;
	UFUNCTION(BlueprintCallable)
	void IncreaseShootsPerSecond(float value);

	//critical damage
	UFUNCTION(BlueprintCallable)
	int GetCriticalChance() const;
	UFUNCTION(BlueprintCallable)
	void IncreaseCriticalChance(int value);
	UFUNCTION(BlueprintCallable)
	float GetCriticalMultiplier() const;
	UFUNCTION(BlueprintCallable)
	void IncreaseCriticalMultiplier(float value);

	//time scale
	UFUNCTION(BlueprintCallable)
	float GetMaxTimeScale() const;
	UFUNCTION(BlueprintCallable)
	void IncrementTimeScale(float amount);

	//kill point multiplier
	UFUNCTION(BlueprintCallable)
	float GetKillPointMultiplier() const;
	UFUNCTION(BlueprintCallable)
	void IncrementKillPointMultiplier(float amount);

	//daily points
	UFUNCTION(BlueprintCallable)
	int GetDailyPoints() const;
	UFUNCTION(BlueprintCallable)
	void IncrementDailyPoints(int amount);

	//max Points
	UFUNCTION(BlueprintCallable)
	void IncrementMaxPoints(int amount);

	UFUNCTION(BlueprintCallable)
	int GetMaxTowerHealth() const;
	UFUNCTION(BlueprintCallable)
	void IncreaseMaxTowerHealth(int amount);
	UFUNCTION(BlueprintCallable)
	void SetTower(ATower* tower);
	UFUNCTION(BlueprintCallable)
	int GetPoints() const;
	UFUNCTION(BlueprintCallable)
	void AddPoints(int amount);
	UFUNCTION(BlueprintCallable)
	bool RemovePoints(int amount);
	UFUNCTION(BlueprintCallable)
	ATower* GetTower() const;
	UFUNCTION(BlueprintCallable)
	bool GetPaused() const;
	UFUNCTION(BlueprintCallable)
	void SetPaused(bool value);
	UFUNCTION(BlueprintCallable)
	int GetRegenPerDay() const;
	UFUNCTION(BlueprintCallable)
	void AddRegenPerDay(int amount);
	UFUNCTION(BlueprintCallable)
	int GetLifeStealChance() const;
	UFUNCTION(BlueprintCallable)
	int GetLifeStealAmount() const;
	UFUNCTION(BlueprintCallable)
	void AddLifeStealChance(int value);
	UFUNCTION(BlueprintCallable)
	void AddLifeStealAmount(int value);
	//time manager
	UFUNCTION(BlueprintCallable)
	ATimeManager* GetTimeManager() const;
	void SetTimeManager(ATimeManager* timeManager);
};
