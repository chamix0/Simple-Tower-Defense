// Fill out your copyright notice in the Description page of Project Settings.


#include "Game_Entities/Tower/Bullets/SimpleBullet.h"

#include "Managers/TowerWorldManager.h"


// Sets default values
ASimpleBullet::ASimpleBullet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetActorEnableCollision(true);

	//create mesh
	m_BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet mesh"));
	m_BulletMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASimpleBullet::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASimpleBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!m_availible)
	{
		//update real color
		m_BulletMesh->SetCustomPrimitiveDataVector4(0, m_currentColor);

		//move towards the tower (0,0)
		Move(DeltaTime);

		//kill bullet if its too far 
		if (FVector::Distance(FVector(0, 0, 0), GetActorLocation()) > 1000.f)
		{
			UnInitializeBullet();
		}
	}
}

void ASimpleBullet::InitializeBullet(FVector target, float speed)
{
	//move to origin
	SetActorLocation(FVector(0, 0, 0));

	//set direction and speed
	m_direction = target.GetSafeNormal2D();
	m_speed = speed;

	//initialize color
	m_targetColor = m_towerWorldManager->GetIsDay() ? m_dayColor : m_nightColor;
	m_currentColor = m_targetColor;
	m_BulletMesh->SetCustomPrimitiveDataVector4(0, m_currentColor);

	//enable tick
	SetActorTickEnabled(true);
}

void ASimpleBullet::UnInitializeBullet()
{
	//make it available again
	SetIsAvailable(true);

	//return it top the pool
	m_towerWorldManager->GetBulletPool().InsertBulletToPool(this);

	//move under the ground
	SetActorLocation(FVector(0, 0, -2000));

	//disable tick
	SetActorTickEnabled(false);
}

bool ASimpleBullet::GetIsAvailable() const
{
	return m_availible;
}

void ASimpleBullet::SetIsAvailable(bool value)
{
	m_availible = value;
}

void ASimpleBullet::Move(float deltaTime)
{
	const FVector newPosition = GetActorLocation() + m_direction * m_speed * deltaTime;
	SetActorLocation(newPosition);
}
