// Fill out your copyright notice in the Description page of Project Settings.


#include "Game_Entities/Enemies/SimpleEnemy.h"

#include "Kismet/GameplayStatics.h"
#include "Managers/TowerWorldManager.h"
#include "Particles/ParticleSystemComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Settings/GameSettings.h"


// Sets default values
ASimpleEnemy::ASimpleEnemy()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetActorEnableCollision(true);

	m_EnemyPivot = CreateDefaultSubobject<USceneComponent>(TEXT("Enemy pivot"));
	m_EnemyPivot->SetupAttachment(RootComponent);

	//create mesh
	m_EnemyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Enemy mesh"));
	m_EnemyMesh->SetupAttachment(m_EnemyPivot);
}

// Called when the game starts or when spawned
void ASimpleEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void ASimpleEnemy::InitializeEnemy(FVector spawnPosition)
{
	//update position
	SetActorLocation(spawnPosition);

	//initialize health
	int MaxOverallHealth = GetDefault<UGameSettings>()->MaxEnemyHealth;
	m_MaxHealth = FMath::RandRange(1, MaxOverallHealth);

	//initialize scale
	float MaxScale = GetDefault<UGameSettings>()->MaxEnemyScale;
	float scale = m_MaxHealth * MaxScale / MaxOverallHealth;
	m_EnemyPivot->SetRelativeScale3D(FVector(scale));

	//update real color

	//initialize color
	m_targetColor = m_towerWorldManager->GetIsDay() ? m_dayColor : m_nightColor;
	m_currentColor = m_targetColor;
	m_EnemyMesh->SetCustomPrimitiveDataVector4(0, m_currentColor);

	//enable tick
	SetActorTickEnabled(true);
}

void ASimpleEnemy::UnInitializeEnemy()
{
	//make it available again
	SetIsAvailable(true);

	//return it top the pool
	m_towerWorldManager->GetEnemyPool().InsertEnemyToPool(this);

	// Create the Niagara Component
	UNiagaraComponent* NiagaraComponentSpawn = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
		GetWorld(), m_ExplosionParticles, GetActorLocation());
	NiagaraComponentSpawn->SetVariableLinearColor("Color", m_currentColor);

	//move under the ground
	SetActorLocation(FVector(0, 0, -1000));

	//disable tick
	SetActorTickEnabled(false);
}

// Called every frame
void ASimpleEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!m_availible)
	{
		//update real color
		m_EnemyMesh->SetCustomPrimitiveDataVector4(0, m_currentColor);

		//move towards the tower (0,0)
		Move(DeltaTime);
	}
}

bool ASimpleEnemy::GetIsAvailable() const
{
	return m_availible;
}

void ASimpleEnemy::SetIsAvailable(bool value)
{
	m_availible = value;
}

void ASimpleEnemy::Move(float deltaTime)
{
	FVector newPosition = FMath::VInterpConstantTo(GetActorLocation(), FVector(0), deltaTime, m_speed);
	SetActorLocation(newPosition);
}
