// Fill out your copyright notice in the Description page of Project Settings.


#include "Game_Entities/Tower/Crosshair/CrosshairActor.h"

#include "Components/WidgetComponent.h"
#include "Game_Entities/Tower/Tower.h"
#include "Managers/TowerWorldManager.h"
#include "Settings/GameSettings.h"
#include "UI/Hud/Crosshair/CrosshairWidget.h"


// Sets default values
ACrosshairActor::ACrosshairActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//create widget component
	m_WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Cross hair widget component"));
	m_WidgetComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACrosshairActor::BeginPlay()
{
	Super::BeginPlay();

	// get crosshair widget
	m_CrosshairWidget = Cast<UCrosshairWidget>(m_WidgetComponent->GetWidget());

	//start with the crosshair hidden
	m_CrosshairWidget->SetRenderOpacity(0);

	//start shoot timer
	m_shootStopwatch.Start();
}

FVector ACrosshairActor::CalculateTargetPoint()
{
	return m_targetToFollow->GetActorLocation() - m_targetToFollow->GetActorLocation().GetSafeNormal2D() * m_lookAhead;
}


// Called every frame
void ACrosshairActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//feed the timer
	M_NoTargetStopWatch.ReceiveTick(DeltaTime);
	m_shootStopwatch.ReceiveTick(DeltaTime);

	//update color
	m_CrosshairWidget->SetColor(m_currentColor);


	if (m_targetToFollow == nullptr)
	{
		m_CrosshairWidget->SetRenderScale(FVector2D(FMath::FInterpTo(m_CrosshairWidget->RenderTransform.Scale.X, 0.5f,
		                                                             DeltaTime,
		                                                             GetDefault<UGameSettings>()->ColorChangeSpeed)));
		//start the timer if it wasn't running
		if (!M_NoTargetStopWatch.isRunning())
		{
			M_NoTargetStopWatch.ReStart();
		}

		//send target request notification
		if (M_NoTargetStopWatch.GetElapsedMiliSeconds() > 100)
		{
			M_NoTargetStopWatch.Reset();
			m_towerWorldManager->BroadCastNotification(UTowerEvent::CROSSHAIR_REQUESTS_TARGET);
		}
		return;
	}

	//check if the target is valid 
	if (m_targetToFollow->GetIsAvailable() || !m_towerWorldManager->GetTower()->GetInRange(
		m_targetToFollow->GetActorLocation()))
	{
		m_targetToFollow = nullptr;
		return;
	}

	//update opacity
	m_CrosshairWidget->SetRenderOpacity(FMath::FInterpConstantTo(m_CrosshairWidget->GetRenderOpacity(),
	                                                             1, DeltaTime,
	                                                             GetDefault<UGameSettings>()->ColorChangeSpeed));
	m_CrosshairWidget->SetRenderScale(FVector2D(FMath::FInterpTo(m_CrosshairWidget->RenderTransform.Scale.X,
	                                                             m_targetToFollow->GetActorScale().X * 4.8f,
	                                                             DeltaTime,
	                                                             GetDefault<UGameSettings>()->ColorChangeSpeed)));
	//move to target with anticipation
	SetActorLocation(FMath::VInterpTo(GetActorLocation(), CalculateTargetPoint(), DeltaTime, m_speed));

	// if the crosshair has reached the target then notify and clear
	if (FVector::Distance(GetActorLocation(), CalculateTargetPoint()) <= m_MinDistanceToTarget)
	{
		m_towerWorldManager->BroadCastNotification(UTowerEvent::CROSSHAIR_REACHED_TARGET);

		float cooldown = 1 / m_towerWorldManager->GetShootsPerSecond();
		if (m_shootStopwatch.GetElapsedSeconds() >= cooldown)
		{
			//shoot
			m_towerWorldManager->GetTower()->ShootBullet(GetActorLocation());

			//restart timer
			m_shootStopwatch.ReStart();
			//get new target
			m_targetToFollow = nullptr;
			m_targetToFollow = m_towerWorldManager->GetTower()->SelectEnemyTarget();
		}
	}
}

void ACrosshairActor::SetTargetToFollow(ASimpleEnemy* target)
{
	m_targetToFollow = target;
}

AActor* ACrosshairActor::GetTarget() const
{
	return m_targetToFollow;
}

FStopWatch ACrosshairActor::GetShootStopWatch() const
{
	return m_shootStopwatch;
}
