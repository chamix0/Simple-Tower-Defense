// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "Game_Entities/SimpleDayNightActor.h"
#include "SimpleEnemy.generated.h"

UCLASS()
class SIMPLETOWERDEFENSE_API ASimpleEnemy : public ASimpleDayNightActor
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* m_EnemyMesh = nullptr;
	UPROPERTY(EditAnywhere)
	USceneComponent* m_EnemyPivot = nullptr;
	UPROPERTY(EditAnywhere)
	float m_health;
	UPROPERTY(EditAnywhere)
	int m_MaxHealth = 10;
	UPROPERTY(EditAnywhere)
	float m_speed = 1;
	UPROPERTY()
	bool m_availible = true;
	UPROPERTY(EditAnywhere)
	UNiagaraSystem* m_ExplosionParticles=nullptr;

public:
	// Sets default values for this actor's properties
	ASimpleEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	void InitializeEnemy(FVector spawnPosition);
	void UnInitializeEnemy();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	bool GetIsAvailable() const;
	void SetIsAvailable(bool value);

private:
	void Move(float deltaTime);
};
