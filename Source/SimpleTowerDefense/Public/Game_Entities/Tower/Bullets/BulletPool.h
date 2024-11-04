// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SimpleBullet.h"
#include "GameFramework/Actor.h"
#include "BulletPool.generated.h"


USTRUCT()
struct FBulletPool
{
	GENERATED_BODY()

	FBulletPool();

	UPROPERTY()
	TArray<ASimpleBullet*> m_AvailibleBullets;


	ASimpleBullet* GetBullet(UWorld* world, TSubclassOf<AActor> templateBullet);

	ASimpleBullet* FindBullet();

	void InsertBulletToPool(ASimpleBullet* bullet);
};
