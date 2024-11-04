// Fill out your copyright notice in the Description page of Project Settings.


#include "Game_Entities/SimpleDayNightActor.h"

#include "Managers/TowerWorldManager.h"
#include "Settings/GameSettings.h"


// Sets default values
ASimpleDayNightActor::ASimpleDayNightActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASimpleDayNightActor::BeginPlay()
{
	Super::BeginPlay();
	//get tower world manager
	m_towerWorldManager = GetWorld()->GetSubsystem<UTowerWorldManager>();
	//subscribe to publisher
	m_towerWorldManager->Subscribe(this);

	//initialize color
	m_targetColor = m_towerWorldManager->GetIsDay() ? m_dayColor : m_nightColor;
	m_targetOppositeColor = m_towerWorldManager->GetIsDay() ? m_nightColor : m_dayColor;
	m_currentColor = m_targetColor;
	m_currentOppositeColor = m_targetOppositeColor;
}

// Called every frame
void ASimpleDayNightActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//interpolate color
	m_currentColor = FMath::CInterpTo(m_currentColor, m_targetColor, DeltaTime,
	                                  GetDefault<UGameSettings>()->ColorChangeSpeed);
	m_currentOppositeColor = FMath::CInterpTo(m_currentOppositeColor, m_targetOppositeColor, DeltaTime,
	                                          GetDefault<UGameSettings>()->ColorChangeSpeed);
}

void ASimpleDayNightActor::update(const UTowerEvent event)
{
	if (event == UTowerEvent::IS_NIGHT)
	{
		m_targetColor = m_nightColor;
		m_targetOppositeColor = m_dayColor;
	}
	else if (event == UTowerEvent::IS_DAY)
	{
		m_targetColor = m_dayColor;
		m_targetOppositeColor = m_nightColor;
	}
}
