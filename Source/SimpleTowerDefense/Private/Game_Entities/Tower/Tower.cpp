// Fill out your copyright notice in the Description page of Project Settings.


#include "Game_Entities/Tower/Tower.h"

#include "Game_Entities/Enemies/SimpleEnemy.h"
#include "Utils/MyDebugUtils.h"


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
	//set up collision
	m_TowerMesh->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnTowerOverlap);
	m_TowerMesh->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnTowerEndOverlap);
}

// Called every frame
void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//update real color
	m_TowerMesh->SetCustomPrimitiveDataVector4(0, m_currentColor);
}

void ATower::OnTowerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                            const FHitResult& SweepResult)
{
	ASimpleEnemy* Enemy = Cast<ASimpleEnemy>(OtherActor);
	if (Enemy != nullptr)
	{
		Enemy->UnInitializeEnemy();
		//make damage to self
	}}

void ATower::OnTowerEndOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                               int32 OtherBodyIndex)
{
	MyDebugUtils::Print("something exited collision");
}
