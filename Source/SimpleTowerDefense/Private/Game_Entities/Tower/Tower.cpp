// Fill out your copyright notice in the Description page of Project Settings.


#include "Game_Entities/Tower/Tower.h"

#include "Game_Entities/Enemies/SimpleEnemy.h"
#include "Game_Entities/Tower/Crosshair/CrosshairActor.h"
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

	//start shooting stopwatch
	m_shootTimer.Start();
}

// Called every frame
void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//feed the timer
	m_shootTimer.ReceiveTick(DeltaTime);

	//update real color
	m_TowerMesh->SetCustomPrimitiveDataVector4(0, m_currentColor);

#if WITH_EDITOR
	//draw debug range
	DrawDebugSphere(GetWorld(), FVector(0, 0, 0), m_towerWorldManager->GetTowerRange(), 32, FColor::Blue);
#endif
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
	}
}

void ATower::OnTowerEndOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                               int32 OtherBodyIndex)
{
	MyDebugUtils::Print("something exited collision");
}

void ATower::update(const UTowerEvent event)
{
	//update from parent
	Super::update(event);

	if (event == UTowerEvent::CROSSHAIR_REQUESTS_TARGET)
	{
		M_CrosshairActor->SetTargetToFollow(SelectEnemyTarget());
	}
	else if (event == UTowerEvent::CROSSHAIR_REACHED_TARGET)
	{
		float cooldown = 1 / m_towerWorldManager->GetShootsPerSecond();
		if (m_shootTimer.GetElapsedSeconds() >= cooldown)
		{
			//shoot
			ShootBullet(M_CrosshairActor->GetActorLocation());

			//get a new target
			M_CrosshairActor->SetTargetToFollow(SelectEnemyTarget());

			//restart timer
			m_shootTimer.ReStart();
		}
	}
}

ASimpleEnemy* ATower::SelectEnemyTarget()
{
	//active enemies
	TArray<ASimpleEnemy*> enemies = m_towerWorldManager->GetEnemyPool().m_ActiveEnemies;

	//find closest enemy
	float minDistance = std::numeric_limits<float>::max();
	ASimpleEnemy* selectedEnemy = nullptr;
	for (ASimpleEnemy*& Enemy : enemies)
	{
		float distance = FVector::Distance(GetActorLocation(), Enemy->GetActorLocation());
		if (distance < minDistance && !Enemy->GetIsAvailable() && distance <= m_towerWorldManager->GetTowerRange())
		{
			minDistance = distance;
			selectedEnemy = Enemy;
		}
	}

	return selectedEnemy;
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
