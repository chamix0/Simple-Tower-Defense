// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObserverPattern/Publisher.h"
#include "Subsystems/WorldSubsystem.h"
#include "TowerWorldManager.generated.h"

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
	bool m_isDay = true;
	int m_numDays;

public:
	bool GetIsNight() const;
	void StartNight();
	void StartDay();
	int GetNumDays();
	void AddDay();

};
