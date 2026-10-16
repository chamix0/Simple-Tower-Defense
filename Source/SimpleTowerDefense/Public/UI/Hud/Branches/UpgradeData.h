// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UpgradeData.generated.h"

class UTowerWorldManager;
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class SIMPLETOWERDEFENSE_API UUpgradeData : public UObject
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText UpgradeName;

	UPROPERTY(EditAnywhere)
	int baseCost = 0;
	
	UPROPERTY(EditAnywhere)
	int CostIncrement = 0;
	
	UPROPERTY(EditAnywhere)
	int unlockDay = 1;

	/*-1 means no limit other, is the limit*/
	UPROPERTY(EditAnywhere)
	int MaxUpgrades = -1;

public:
	/// uses the item, the implementation is done in blueprint
	UFUNCTION(BlueprintImplementableEvent)
	void ApplyUpgrade(UTowerWorldManager* WorldManager);
};
