﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Game_Entities/Other/GroundActor.h"


// Sets default values
AGroundActor::AGroundActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//create mesh
	m_GroundMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor mesh"));
	m_GroundMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AGroundActor::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void AGroundActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//update real color
	m_GroundMesh->SetCustomPrimitiveDataVector4(0, m_currentColor);
}