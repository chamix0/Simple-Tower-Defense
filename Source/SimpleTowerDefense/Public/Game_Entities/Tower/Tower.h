// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Game_Entities/SimpleDayNightActor.h"
#include "Managers/TowerWorldManager.h"
#include "ObserverPattern/Publisher.h"
#include "Utils/StopWatch.h"
#include "Tower.generated.h"

class ACrosshairActor;

UCLASS()
class SIMPLETOWERDEFENSE_API ATower : public ASimpleDayNightActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<ASimpleBullet> m_bulletTemplate;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* m_TowerMesh = nullptr;
	UPROPERTY(EditAnywhere)
	ACrosshairActor* M_CrosshairActor = nullptr;
	//shoot cooldown
	FStopWatch m_shootTimer;


public:
	// Sets default values for this actor's properties
	ATower();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void OnTowerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                    const FHitResult& SweepResult);
	UFUNCTION()
	void OnTowerEndOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor,
	                       class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	virtual void update(const UTowerEvent event) override;
	ASimpleEnemy* SelectEnemyTarget();
	void ShootBullet(FVector target);
};
