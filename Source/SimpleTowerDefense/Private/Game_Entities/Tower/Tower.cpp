// Fill out your copyright notice in the Description page of Project Settings.


#include "Game_Entities/Tower/Tower.h"


// Sets default values
ATower::ATower()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//create mesh
	m_TowerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tower mesh"));
	m_TowerMesh->SetupAttachment(RootComponent);
}



// Called when the game starts or when spawned
void ATower::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//update real color
	m_TowerMesh->SetCustomPrimitiveDataVector4(0, m_currentColor);
}
