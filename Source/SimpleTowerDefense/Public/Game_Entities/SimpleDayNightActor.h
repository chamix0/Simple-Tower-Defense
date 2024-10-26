﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObserverPattern/Observer.h"
#include "SimpleDayNightActor.generated.h"


class UTowerWorldManager;

UCLASS()
class SIMPLETOWERDEFENSE_API ASimpleDayNightActor : public AActor, public Observer
{
	GENERATED_BODY()

protected:
	//world manager
	UPROPERTY()
	UTowerWorldManager* m_towerWorldManager = nullptr;

	//colors
	UPROPERTY(EditAnywhere)
	FColor m_dayColor = FColor::White;
	UPROPERTY(EditAnywhere)
	FColor m_nightColor = FColor::Black;
	FLinearColor m_currentColor;
	FLinearColor m_targetColor;
	UPROPERTY(EditAnywhere)
	float m_ColorChangeSpeed = 5.f;

public:
	// Sets default values for this actor's properties
	ASimpleDayNightActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void update(const UTowerEvent event) override;
};