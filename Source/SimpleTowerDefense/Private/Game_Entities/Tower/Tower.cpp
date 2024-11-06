// Fill out your copyright notice in the Description page of Project Settings.


#include "Game_Entities/Tower/Tower.h"

#include "Game_Entities/Enemies/SimpleEnemy.h"
#include "Game_Entities/Tower/Crosshair/CrosshairActor.h"
#include "Kismet/GameplayStatics.h"
#include "UI/GameBaseWidget.h"
#include "UI/Hud/HudWidget.h"
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

	//register tower
	m_towerWorldManager->SetTower(this);

	// Create UI Base and add it To Screen
	GameBaseWidget = CreateWidget<UGameBaseWidget>(GetGameInstance(), BaseWidgetClass, FName("Game UI Base"));

	if (GameBaseWidget != nullptr)
	{
		//add ui base to screen
		GameBaseWidget->AddToViewport();
		//get HUD from widget
		HudWidget = GameBaseWidget->GetHudWidget();
	}

	//set input mode
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeGameAndUI());

	//set up collision
	m_TowerMesh->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnTowerOverlap);
	m_TowerMesh->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnTowerEndOverlap);

	//initialize health
	SetHealth(m_towerWorldManager->GetMaxTowerHealth());


	//create first crosshair
	AddCrossHair();
}

// Called every frame
void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//feed the timer
	damageTimer.ReceiveTick(DeltaTime);

	if (damageTimer.isRunning())
	{
		//update real color
		m_TowerMesh->SetCustomPrimitiveDataVector4(0, DamageColor);
		if (damageTimer.GetElapsedMiliSeconds() > damageEffectMilliseconds)
		{
			damageTimer.Reset();
		}
	}
	else
	{
		//update real color
		m_TowerMesh->SetCustomPrimitiveDataVector4(0, m_currentColor);
	}
}

UHudWidget* ATower::GetHud() const
{
	return HudWidget;
}

UGameBaseWidget* ATower::GetGameBaseWidget() const
{
	return GameBaseWidget;
}

void ATower::OnTowerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                            const FHitResult& SweepResult)
{
	ASimpleEnemy* Enemy = Cast<ASimpleEnemy>(OtherActor);
	if (Enemy != nullptr)
	{
		//make damage to self
		TakeDamage(Enemy->GetHealth());

		//un initialize enemy
		Enemy->UnInitializeEnemy();
	}
}

void ATower::OnTowerEndOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                               int32 OtherBodyIndex)
{
}

void ATower::update(const UTowerEvent event)
{
	//update from parent
	Super::update(event);

	if (event == UTowerEvent::CROSSHAIR_REQUESTS_TARGET)
	{
		for (ACrosshairActor*& Crosshair : M_CrosshairActors)
		{
			if (Crosshair->GetTarget() == nullptr)
			{
				Crosshair->SetTargetToFollow(SelectEnemyTarget());
			}
		}
	}
	else if (event == UTowerEvent::CROSSHAIR_REACHED_TARGET)
	{
		// float cooldown = 1 / m_towerWorldManager->GetShootsPerSecond();
		// if (m_shootTimer.GetElapsedSeconds() >= cooldown)
		// {
		// 	//shoot
		// 	ShootBullet(M_CrosshairActor->GetActorLocation());
		//
		// 	//get a new target
		// 	M_CrosshairActor->SetTargetToFollow(SelectEnemyTarget());
		//
		// 	//restart timer
		// 	m_shootTimer.ReStart();
		// }
	}
	else if (event == UTowerEvent::IS_DAY)
	{
		//regen life
		AddHealth(m_towerWorldManager->GetRegenPerDay());

		//show notification
		if (m_towerWorldManager->GetRegenPerDay() > 0)
		{
			GetHud()->PushNotification(
				"Regained " + FString::FromInt(m_towerWorldManager->GetRegenPerDay()) + " Health points", 2.f);
		}
		//add points
		m_towerWorldManager->AddPoints(m_towerWorldManager->GetDailyPoints());
	}
}

ASimpleEnemy* ATower::SelectEnemyTarget()
{
	switch (m_currentShootingPolicy)
	{
	case UShootingPolicy::CLOSEST:
		return SelectClosestEnemyTarget();
	case UShootingPolicy::FURTHEST:
		return SelectFarthesEnemyTarget();
	case UShootingPolicy::STRONGUEST:
		return SelectStronguestEnemyTarget();
	case UShootingPolicy::WEAKEST:
		return SelectweakestEnemyTarget();
	default:
		return SelectClosestEnemyTarget();
	}
}

ASimpleEnemy* ATower::SelectClosestEnemyTarget()
{
	//active enemies
	TArray<ASimpleEnemy*> enemies = m_towerWorldManager->GetEnemyPool().m_ActiveEnemies;


	//find closest enemy
	float minDistance = std::numeric_limits<float>::max();
	ASimpleEnemy* selectedEnemy = nullptr;
	for (ASimpleEnemy*& Enemy : enemies)
	{
		float distance = FVector::Distance(GetActorLocation(), Enemy->GetActorLocation());
		if (distance < minDistance && !Enemy->GetIsAvailable() && GetInRange(Enemy->GetActorLocation()) && !
			IsTargetPicked(Enemy))
		{
			minDistance = distance;
			selectedEnemy = Enemy;
		}
	}

	return selectedEnemy;
}

ASimpleEnemy* ATower::SelectFarthesEnemyTarget()
{
	//active enemies
	TArray<ASimpleEnemy*> enemies = m_towerWorldManager->GetEnemyPool().m_ActiveEnemies;

	//find closest enemy
	float maxDistance = 0;
	ASimpleEnemy* selectedEnemy = nullptr;
	for (ASimpleEnemy*& Enemy : enemies)
	{
		float distance = FVector::Distance(GetActorLocation(), Enemy->GetActorLocation());
		if (distance > maxDistance && !Enemy->GetIsAvailable() && GetInRange(Enemy->GetActorLocation()) && !
			IsTargetPicked(Enemy))
		{
			maxDistance = distance;
			selectedEnemy = Enemy;
		}
	}

	return selectedEnemy;
}


ASimpleEnemy* ATower::SelectStronguestEnemyTarget()
{
	//active enemies
	TArray<ASimpleEnemy*> enemies = m_towerWorldManager->GetEnemyPool().m_ActiveEnemies;

	//find closest enemy
	float maxHealth = 0;
	ASimpleEnemy* selectedEnemy = nullptr;
	for (ASimpleEnemy*& Enemy : enemies)
	{
		float health = Enemy->GetMaxHealth();
		// float distance = FVector::Distance(GetActorLocation(), Enemy->GetActorLocation());
		if (health > maxHealth && !Enemy->GetIsAvailable() && GetInRange(
				Enemy->GetActorLocation()) && !
			IsTargetPicked(Enemy))
		{
			maxHealth = health;
			selectedEnemy = Enemy;
		}
	}

	return selectedEnemy;
}

ASimpleEnemy* ATower::SelectweakestEnemyTarget()
{
	//active enemies
	TArray<ASimpleEnemy*> enemies = m_towerWorldManager->GetEnemyPool().m_ActiveEnemies;

	//find closest enemy
	float minHealth = std::numeric_limits<float>::max();
	ASimpleEnemy* selectedEnemy = nullptr;
	for (ASimpleEnemy*& Enemy : enemies)
	{
		float health = Enemy->GetMaxHealth();
		// float distance = FVector::Distance(GetActorLocation(), Enemy->GetActorLocation());
		if (health < minHealth && !Enemy->GetIsAvailable() && GetInRange(Enemy->GetActorLocation()) && !
			IsTargetPicked(Enemy))
		{
			minHealth = health;
			selectedEnemy = Enemy;
		}
	}

	return selectedEnemy;
}

bool ATower::IsTargetPicked(ASimpleEnemy* target)
{
	for (ACrosshairActor*& Crosshair : M_CrosshairActors)
	{
		if (Crosshair->GetTarget() == target)
		{
			return true;
		}
	}
	return false;
}

bool ATower::GetInRange(FVector target)
{
	float rx = -m_towerWorldManager->GetTowerRange(); // x position
	float ry = -m_towerWorldManager->GetTowerRange(); // y position
	float rw = m_towerWorldManager->GetTowerRange() * 2; // width
	float rh = m_towerWorldManager->GetTowerRange() * 2; // height

	if (target.X >= rx && // right of the left edge AND
		target.X <= rx + rw && // left of the right edge AND
		target.Y >= ry && // below the top AND
		target.Y <= ry + rh)
	{
		// above the bottom
		return true;
	}
	return false;
}

void ATower::SetShootingPolicy(UShootingPolicy policy)
{
	m_currentShootingPolicy = policy;
}

UShootingPolicy ATower::GetCurrentShootingPolicy() const
{
	return m_currentShootingPolicy;
}


void ATower::ShootBullet(FVector target)
{
	if (m_bulletTemplate != nullptr)
	{
		ASimpleBullet* Bullet = m_towerWorldManager->GetBulletPool().GetBullet(GetWorld(), m_bulletTemplate);
		Bullet->InitializeBullet(target, m_towerWorldManager->GetBulletsSpeed());
		return;
	}
	MyDebugUtils::Print("NO BULLET TEMPLATE GIVEN TO ENEMY SPAWNER!!!", FColor::Red);
}

void ATower::TakeDamage(float amount)
{
	SetHealth(FMath::Max(m_health - amount, 0));
	damageTimer.ReStart();
	if (m_health <= 0)
	{
		//do something

		GameBaseWidget->PushWidget(EndScreenWidgetClass);
	}
}

void ATower::SetHealth(float value)
{
	m_health = FMath::Min(value, m_towerWorldManager->GetMaxTowerHealth());
	HudWidget->UpdateHealth(m_health, m_towerWorldManager->GetMaxTowerHealth());
}

void ATower::AddHealth(float value)
{
	SetHealth(FMath::Min(m_health + value, m_towerWorldManager->GetMaxTowerHealth()));
}

void ATower::AddCrossHair()
{
	if (m_crosshairTemplate != nullptr)
	{
		//no available enemy so create one 
		FActorSpawnParameters SpawnInfo;
		AActor* spawnedActor = GetWorld()->SpawnActor<AActor>(m_crosshairTemplate, FVector(0, 0, 0), FRotator(0, 0, 0),
		                                                      SpawnInfo);

		//add to a folder to make it cleaner on editor
#if WITH_EDITOR
		spawnedActor->SetFolderPath("Crosshairs");
#endif

		//get the enemy reference
		ACrosshairActor* Crosshair = Cast<ACrosshairActor>(spawnedActor);
		M_CrosshairActors.Add(Crosshair);
		return;
	}
	MyDebugUtils::Print("NO ENEMY TEMPLATE GIVEN TO ENEMY SPAWNER!!!", FColor::Red);
}

float ATower::GetHealth() const
{
	return m_health;
}

int ATower::GetNumTargets() const
{
	return M_CrosshairActors.Num();
}
