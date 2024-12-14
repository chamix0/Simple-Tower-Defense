// Fill out your copyright notice in the Description page of Project Settings.


#include "Game_Entities/Other/GroundActor.h"


// Sets default values
AGroundActor::AGroundActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//create mesh
	m_GroundMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor mesh"));
	m_GroundMesh->SetupAttachment(RootComponent);

	//create range widget component
	m_rangeWidgetcomponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Range Widget Component"));
	m_rangeWidgetcomponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AGroundActor::BeginPlay()
{
	Super::BeginPlay();
	m_rangeWidgetcomponent->SetDrawSize(FVector2D(m_towerWorldManager->GetTowerRange()*2.f));
	m_rangeWidgetcomponent->GetWidget()->SetColorAndOpacity(m_currentOppositeColor);
	m_rangeWidgetcomponent->SetTickableWhenPaused(true);
}


// Called every frame
void AGroundActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//update real color
	m_GroundMesh->SetCustomPrimitiveDataVector4(0, m_currentColor);

	//update range widget size
	m_rangeWidgetcomponent->GetWidget()->SetColorAndOpacity(m_currentOppositeColor);
}

void AGroundActor::update(const UTowerEvent event)
{
	Super::update(event);

	if (event==UTowerEvent::STATS_CHANGED)
	{
		m_rangeWidgetcomponent->SetDrawSize(FVector2D(m_towerWorldManager->GetTowerRange() * 2.f));
	}
}
