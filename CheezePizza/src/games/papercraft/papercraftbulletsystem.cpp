#include "cheezepizza.h"
#include "papercraftbulletsystem.h"

PapercraftBulletSystem::PapercraftBulletSystem()
	: FreeIndex(0)
{
	for(int Index = 0; Index < MAX_BULLETS; ++Index)
	{
		BulletIndexer[Index] = Index;
	}

	Behaviors[BBT_Default] = new PapercraftBulletBehaviorDefault();
}

PapercraftBulletSystem::~PapercraftBulletSystem()
{
}

bool PapercraftBulletSystem::SpawnBullet(Bullet& Definition)
{
	bool bSpawnedBullet = false;

	if(CanSpawnBullet())
	{
		// Clear the bullet's variables because they can continue 
		// values stored from the last use of this bullet
		BulletPool[FreeIndex].ResetToDefaults();

		BulletPool[FreeIndex] = Definition;

		// Increment the pointer to the next free bullet in the pool
		FreeIndex += 1;

		bSpawnedBullet = true;
	}

	return bSpawnedBullet;
}

void PapercraftBulletSystem::Tick(float DeltaTime)
{
	if(FreeIndex > 0)
	{
		for(int Index = 0; Index < FreeIndex; ++Index)
		{
			Behaviors[BulletPool[Index].Behavior]->TickBullet(DeltaTime, BulletPool[Index]);
		}
	}
}

// EOF
