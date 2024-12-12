// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "Components/WidgetComponent.h"
#include "Game_Entities/SimpleDayNightActor.h"
#include "UI/Basics/HealthBar.h"
#include "Utils/StopWatch.h"
#include "SimpleEnemy.generated.h"

UCLASS()
class SIMPLETOWERDEFENSE_API ASimpleEnemy : public ASimpleDayNightActor
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	bool m_availible = true;
private:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* m_EnemyMesh = nullptr;
	UPROPERTY(EditAnywhere)
	USceneComponent* m_EnemyPivot = nullptr;
	UPROPERTY(EditDefaultsOnly)
	UWidgetComponent* m_healthBarComponent = nullptr;
	UPROPERTY()
	UHealthBar* m_healthBarWidget = nullptr;

	UPROPERTY(EditAnywhere)
	float m_health;
	UPROPERTY(EditAnywhere)
	float m_MaxHealth = 10;
	UPROPERTY(EditAnywhere)
	float m_speed = 1;

	bool m_isCriticalDamage = false;
	float targetSpeed;

	UPROPERTY(EditAnywhere)
	UNiagaraSystem* m_ExplosionParticles = nullptr;
	FStopWatch damageTimer;
	UPROPERTY(EditAnywhere)
	FLinearColor DamageColor = FColor::Red;
	UPROPERTY(EditAnywhere)
	FLinearColor CriticalColor = FColor::Yellow;
	UPROPERTY(EditAnywhere)
	int damageEffectMilliseconds = 100;

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
	float GetHealth() const;
	float GetMaxHealth() const;
protected:
	void Move(float deltaTime);
	
private:
	UFUNCTION()
	void OnEnemyOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                    const FHitResult& SweepResult);
	UFUNCTION()
	void OnEnemyEndOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor,
	                       class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	void RemoveHealth(int amount);
	void DamageColorUpdate();
};
