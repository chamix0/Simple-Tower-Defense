// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TowerWorldManager.h"
#include "GameFramework/Actor.h"
#include "Utils/StopWatch.h"
#include "TimeManager.generated.h"

UCLASS()
class SIMPLETOWERDEFENSE_API ATimeManager : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY()
	UTowerWorldManager* m_towerWorldManager=nullptr;
	FStopWatch m_dayStopwatch;
	bool halfDayReached = false;

public:
	// Sets default values for this actor's properties
	ATimeManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
