// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Game_Entities/SimpleDayNightActor.h"
#include "Managers/TowerWorldManager.h"
#include "ObserverPattern/Publisher.h"
#include "Utils/StopWatch.h"
#include "Tower.generated.h"

class UHudWidget;
class UGameBaseWidget;
class ACrosshairActor;

UCLASS()
class SIMPLETOWERDEFENSE_API ATower : public ASimpleDayNightActor
{
	GENERATED_BODY()

private:
	//class of the UI base to be created
	UPROPERTY(EditAnywhere, Category="UI", meta=(DisplayName = "Widget Base class"))
	TSubclassOf<UGameBaseWidget> BaseWidgetClass;
	UPROPERTY()
	UGameBaseWidget* GameBaseWidget = nullptr;
	UPROPERTY()
	UHudWidget* HudWidget = nullptr;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ASimpleBullet> m_bulletTemplate;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* m_TowerMesh = nullptr;
	UPROPERTY(EditAnywhere)
	ACrosshairActor* M_CrosshairActor = nullptr;
	//shooting policy
	UPROPERTY()
	UShootingPolicy m_currentShootingPolicy = UShootingPolicy::CLOSEST;
	
	//shoot cooldown
	FStopWatch m_shootTimer;

	//health
	UPROPERTY(EditAnywhere)
	float m_health = 1;

	//damage
	FStopWatch damageTimer;
	UPROPERTY(EditAnywhere)
	FLinearColor DamageColor = FColor::Red;
	UPROPERTY(EditAnywhere)
	int damageEffectMilliseconds = 100;

public:
	// Sets default values for this actor's properties
	ATower();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UHudWidget* GetHud() const;
	UGameBaseWidget* GetGameBaseWidget() const;
	void SetShootingPolicy(UShootingPolicy policy);
	UShootingPolicy GetCurrentShootingPolicy() const;
private:
	UFUNCTION()
	void OnTowerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                    const FHitResult& SweepResult);
	UFUNCTION()
	void OnTowerEndOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor,
	                       class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	virtual void update(const UTowerEvent event) override;
	/*shooting policy*/
	ASimpleEnemy* SelectEnemyTarget();
	ASimpleEnemy* SelectClosestEnemyTarget();
	ASimpleEnemy* SelectFarthesEnemyTarget();
	ASimpleEnemy* SelectStronguestEnemyTarget();
	ASimpleEnemy* SelectweakestEnemyTarget();

public:
	void ShootBullet(FVector target);
	void TakeDamage(float amount);
	void SetHealth(float value);
	void AddHealth(float value);

	
};
