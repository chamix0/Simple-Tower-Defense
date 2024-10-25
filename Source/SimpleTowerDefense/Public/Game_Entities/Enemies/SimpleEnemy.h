// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game_Entities/SimpleDayNightActor.h"
#include "SimpleEnemy.generated.h"

UCLASS()
class SIMPLETOWERDEFENSE_API ASimpleEnemy : public ASimpleDayNightActor
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* m_EnemyMesh = nullptr;
	UPROPERTY(EditAnywhere)
	float m_health;
	UPROPERTY(EditAnywhere)
	int m_MaxHealth = 10;

public:
	// Sets default values for this actor's properties
	ASimpleEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
