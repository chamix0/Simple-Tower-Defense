// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SimpleEnemy.h"
#include "SimpleMenuEnemy.generated.h"
/*This enemy is only for the main menu, is not a real enemy*/
UCLASS()
class SIMPLETOWERDEFENSE_API ASimpleMenuEnemy : public ASimpleEnemy
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASimpleMenuEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
