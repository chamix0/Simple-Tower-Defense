// Fill out your copyright notice in the Description page of Project Settings.


#include "Game_Entities/SimpleDayNightActor.h"


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
	m_targetColor = m_dayColor;
	m_currentColor = m_targetColor;
}

// Called every frame
void ASimpleDayNightActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//interpolate color
	m_currentColor = FMath::CInterpTo(m_currentColor, m_targetColor, DeltaTime, m_ColorChangeSpeed);
}

void ASimpleDayNightActor::update(const UTowerEvent event)
{
	if (event == UTowerEvent::IS_NIGHT)
	{
		m_targetColor = m_nightColor;
	}
	else if (event == UTowerEvent::IS_DAY)
	{
		m_targetColor = m_dayColor;
	}	
}

