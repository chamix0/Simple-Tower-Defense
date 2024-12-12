// Fill out your copyright notice in the Description page of Project Settings.


#include "Game_Entities/Enemies/SimpleEnemy.h"

#include "Kismet/GameplayStatics.h"
#include "Managers/TowerWorldManager.h"
#include "Particles/ParticleSystemComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Game_Entities/Tower/Tower.h"
#include "Settings/GameSettings.h"
#include "UI/Hud/HudWidget.h"


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

	//create healthbar component
	m_healthBarComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Health bar widget component"));
	m_healthBarComponent->SetupAttachment(m_EnemyPivot);
}

// Called when the game starts or when spawned
void ASimpleEnemy::BeginPlay()
{
	Super::BeginPlay();

	//set up collision
	m_EnemyMesh->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnEnemyOverlap);
	m_EnemyMesh->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnEnemyEndOverlap);

	//get health bar widget


	m_healthBarWidget = Cast<UHealthBar>(m_healthBarComponent->GetWidget());
}

void ASimpleEnemy::InitializeEnemy(FVector spawnPosition)
{
	targetSpeed = GetDefault<UGameSettings>()->EnemyOutOfRangeSpeed;
	//stop damage timer
	damageTimer.Reset();
	//update position
	SetActorLocation(spawnPosition);

	//initialize health
	float MaxOverallHealth = GetDefault<UGameSettings>()->MaxEnemyHealth + GetDefault<UGameSettings>()->MaxEnemyHealth *
		m_towerWorldManager->GetNumDays() * GetDefault<
			UGameSettings>()->DifficultyIncrement;
	m_MaxHealth = FMath::RandRange(0.1f, MaxOverallHealth);
	m_health = m_MaxHealth;


	//initialize scale
	float MaxScale = GetDefault<UGameSettings>()->MaxEnemyScale;
	float scale = m_MaxHealth * MaxScale / MaxOverallHealth;
	m_EnemyPivot->SetRelativeScale3D(FVector(scale));


	if (m_healthBarWidget != nullptr)
	{
		m_healthBarWidget->SetValue(m_health, m_MaxHealth);
		m_healthBarWidget->Show();
		m_healthBarWidget->SetRenderScale(FVector2D(scale));
	}

	//initialize speed
	float MaxOverallSpeed = GetDefault<UGameSettings>()->MaxEnemySpeed + GetDefault<UGameSettings>()->MaxEnemySpeed *
		m_towerWorldManager->GetNumDays() * GetDefault<
			UGameSettings>()->DifficultyIncrement;
	float MinOverallSpeed = GetDefault<UGameSettings>()->MinEnemySpeed + GetDefault<UGameSettings>()->MinEnemySpeed *
		m_towerWorldManager->GetNumDays() * GetDefault<
			UGameSettings>()->DifficultyIncrement;
	m_speed = FMath::RandRange(MinOverallSpeed, MaxOverallSpeed);

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
	//stop damage timer
	damageTimer.Reset();

	//make it available again
	SetIsAvailable(true);

	//hide healthbar

	if (m_healthBarWidget != nullptr)
	{
		m_healthBarWidget->Hide();
	}

	//return it top the pool
	m_towerWorldManager->GetEnemyPool().InsertEnemyToPool(this);

	// Create the Niagara Component
	UNiagaraComponent* NiagaraComponentSpawn = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
		GetWorld(), m_ExplosionParticles, GetActorLocation());
	if (NiagaraComponentSpawn != nullptr)
	{
		NiagaraComponentSpawn->SetVariableLinearColor("Color", m_currentColor);
	}

	//move under the ground
	SetActorLocation(FVector(0, 0, -1000));

	//disable tick
	SetActorTickEnabled(false);
}

// Called every frame
void ASimpleEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//feed the timer
	damageTimer.ReceiveTick(DeltaTime);

	if (!m_availible)
	{
		DamageColorUpdate();

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

float ASimpleEnemy::GetHealth() const
{
	return m_health;
}

float ASimpleEnemy::GetMaxHealth() const
{
	return m_MaxHealth;
}

void ASimpleEnemy::Move(float deltaTime)
{
	if (m_towerWorldManager->GetTower() != nullptr)
	{
		targetSpeed = FMath::FInterpTo(targetSpeed, m_towerWorldManager->GetTower()->GetInRange(GetActorLocation())
			                                            ? m_speed
			                                            : GetDefault<UGameSettings>()->EnemyOutOfRangeSpeed, deltaTime,
		                               GetDefault<UGameSettings>()->ColorChangeSpeed);
	}
	FVector newPosition = FMath::VInterpConstantTo(GetActorLocation(), FVector(0), deltaTime, targetSpeed);
	SetActorLocation(newPosition);
}

void ASimpleEnemy::OnEnemyOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                  const FHitResult& SweepResult)
{
	ASimpleBullet* bullet = Cast<ASimpleBullet>(OtherActor);
	if (bullet != nullptr)
	{
		bullet->UnInitializeBullet();
		float criticalDamage = 0;
		int rand = FMath::RandRange(0, 100);
		m_isCriticalDamage = false;
		if (rand < m_towerWorldManager->GetCriticalChance())
		{
			m_towerWorldManager->GetTower()->GetHud()->PushNotification("Critical HIT", 0.5f);
			criticalDamage += m_towerWorldManager->GetDamage() * m_towerWorldManager->GetCriticalMultiplier();
			m_isCriticalDamage = true;
		}
		RemoveHealth(bullet->GetDamage() + m_towerWorldManager->GetDamage() + criticalDamage);
	}
}

void ASimpleEnemy::OnEnemyEndOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                     int32 OtherBodyIndex)
{
}

void ASimpleEnemy::RemoveHealth(int amount)
{
	m_health = FMath::Max(0, m_health - amount);

	if (m_healthBarWidget != nullptr)
	{
		m_healthBarWidget->SetValue(m_health, m_MaxHealth);
	}
	damageTimer.ReStart();

	//kill the enemy when reached 0
	if (m_health <= 0)
	{
		UnInitializeEnemy();
		m_towerWorldManager->AddPoints(FMath::Max(1, m_MaxHealth / 2) * m_towerWorldManager->GetKillPointMultiplier());

		//life steal
		int randomNum = FMath::RandRange(0, 100);
		if (randomNum <= m_towerWorldManager->GetLifeStealChance())
		{
			int quantity = FMath::Min(m_MaxHealth, m_towerWorldManager->GetLifeStealAmount());
			m_towerWorldManager->GetTower()->GetHud()->PushNotification(
				"Stole " + FString::FromInt(quantity) + " Health points from enemy's life", 0.5f);
			m_towerWorldManager->GetTower()->AddHealth(quantity);
		}
	}
}

void ASimpleEnemy::DamageColorUpdate()
{
	if (damageTimer.isRunning())
	{
		//update real color
		m_EnemyMesh->SetCustomPrimitiveDataVector4(0, m_isCriticalDamage ? CriticalColor : DamageColor);
		if (damageTimer.GetElapsedMiliSeconds() > damageEffectMilliseconds)
		{
			damageTimer.Reset();
		}
	}
	else
	{
		//update real color
		m_EnemyMesh->SetCustomPrimitiveDataVector4(0, m_currentColor);
	}
}
