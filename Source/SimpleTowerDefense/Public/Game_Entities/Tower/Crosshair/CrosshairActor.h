// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game_Entities/SimpleDayNightActor.h"
#include "Game_Entities/Enemies/SimpleEnemy.h"
#include "Utils/StopWatch.h"
#include "CrosshairActor.generated.h"

class UCrosshairWidget;
class UWidgetComponent;

UCLASS()
class SIMPLETOWERDEFENSE_API ACrosshairActor : public ASimpleDayNightActor
{
	GENERATED_BODY()

private:
	//widget component
	UPROPERTY(EditDefaultsOnly)
	UWidgetComponent* m_WidgetComponent = nullptr;

	//actual widget
	UPROPERTY()
	UCrosshairWidget* m_CrosshairWidget = nullptr;

	//target to follow
	UPROPERTY()
	ASimpleEnemy* m_targetToFollow = nullptr;

	//no target stopwatch
	FStopWatch M_NoTargetStopWatch;
	FStopWatch m_shootStopwatch;
	//parameters
	UPROPERTY(EditAnywhere)
	float m_speed = 1.f;
	UPROPERTY(EditAnywhere)
	float m_MinDistanceToTarget = 1.f;
	UPROPERTY(EditAnywhere)
	float m_lookAhead=10.f;
	
public:
	// Sets default values for this actor's properties
	ACrosshairActor();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetTargetToFollow(ASimpleEnemy* target);
	AActor* GetTarget()const;
	FStopWatch GetShootStopWatch()const;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	FVector CalculateTargetPoint();


};
