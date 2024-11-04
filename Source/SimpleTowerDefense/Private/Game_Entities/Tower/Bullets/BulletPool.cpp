// Fill out your copyright notice in the Description page of Project Settings.


#include "Game_Entities/Tower/Bullets/BulletPool.h"


FBulletPool::FBulletPool()
{
}

ASimpleBullet* FBulletPool::GetBullet(UWorld* world, TSubclassOf<AActor> templateBullet)
{
	//try get an bullet
	ASimpleBullet* bullet = FindBullet();
	if (bullet != nullptr)
	{
		//mark as its not a available
		bullet->SetIsAvailable(false);
		return bullet;
	}

	//no available bullet so create one 
	FActorSpawnParameters SpawnInfo;
	AActor* spawnedActor = world->SpawnActor<AActor>(templateBullet, FVector(0, 0, -1000), FRotator(), SpawnInfo);

	//add to a folder to make it cleaner on editor
#if WITH_EDITOR
	spawnedActor->SetFolderPath("BulletPool");
#endif

	//get the bullet reference
	bullet = Cast<ASimpleBullet>(spawnedActor);

	//make the enemy not available
	bullet->SetIsAvailable(false);


	return bullet;
}

ASimpleBullet* FBulletPool::FindBullet()
{
	//create a copy to safely remove elements
	TArray<ASimpleBullet*> aux = m_AvailibleBullets;

	for (int i = 0; i < aux.Num(); i++)
	{
		ASimpleBullet* Bullet = aux[i];
		if (Bullet->GetIsAvailable())
		{
			//remove available enemy from array
			m_AvailibleBullets.Remove(Bullet);

			//return bullet
			return Bullet;
		}
	}
	return nullptr;
}

void FBulletPool::InsertBulletToPool(ASimpleBullet* bullet)
{
	m_AvailibleBullets.AddUnique(bullet);
}
