// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game_Entities/SimpleDayNightActor.h"
#include "SimpleBullet.generated.h"

UCLASS()
class SIMPLETOWERDEFENSE_API ASimpleBullet : public ASimpleDayNightActor
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* m_BulletMesh = nullptr;
	UPROPERTY(EditAnywhere)
	float m_speed = 1;
	UPROPERTY()
	bool m_availible = true;
	UPROPERTY()
	int m_damage = 0;
	//values
	FVector m_direction = FVector();

public:
	// Sets default values for this actor's properties
	ASimpleBullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void InitializeBullet(FVector target, float speed);
	void UnInitializeBullet();

	bool GetIsAvailable() const;
	void SetIsAvailable(bool value);
	int GetDamage() const;
	void SetDamage(int value);

private:
	void Move(float deltaTime);
};
