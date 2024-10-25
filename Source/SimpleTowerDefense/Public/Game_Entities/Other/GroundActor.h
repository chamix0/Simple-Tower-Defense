// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Game_Entities/SimpleDayNightActor.h"
#include "Managers/TowerWorldManager.h"
#include "ObserverPattern/Observer.h"
#include "GroundActor.generated.h"

UCLASS()
class SIMPLETOWERDEFENSE_API AGroundActor : public ASimpleDayNightActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* m_GroundMesh = nullptr;

public:
	// Sets default values for this actor's properties
	AGroundActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
