// Fill out your copyright notice in the Description page of Project Settings.


#include "Game_Entities/Enemies/SimpleMenuEnemy.h"


// Sets default values
ASimpleMenuEnemy::ASimpleMenuEnemy()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASimpleMenuEnemy::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASimpleMenuEnemy::Tick(float DeltaTime)
{
	if (!m_availible)
	{
		Move(DeltaTime);
	}

	if (FVector2D::Distance(FVector2D(GetActorLocation().X, GetActorLocation().Y), FVector2D(0)) < 10.f)
	{
		UnInitializeEnemy();
	}
}
