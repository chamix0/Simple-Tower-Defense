// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Game_Entities/Enemies/SimpleEnemy.h"
#include "SpecialDaysEnemies.generated.h"

USTRUCT(Blueprintable)
struct FDayEnemiesInput
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<ASimpleEnemy>> Enemies;
	
};

/**
 * 
 */
UCLASS()
class SIMPLETOWERDEFENSE_API USpecialDaysEnemies : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(editAnywhere)
	TMap<int, FDayEnemiesInput> DayStartEnemies;
	UPROPERTY(editAnywhere)
	TMap<int, FDayEnemiesInput> HalfDayEnemies;
	
};
