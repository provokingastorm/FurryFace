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
	for(int i = 0; i < BBT_Max; ++i)
	{
		if(Behaviors[i] != NULL)
		{
			delete Behaviors[i];
			Behaviors[i] = NULL;
		}
	}
}

bool PapercraftBulletSystem::SpawnBullet(Bullet& Definition)
{
	bool bSpawnedBullet = false;

	if(CanSpawnBullet())
	{
		const int PoolIndex = BulletIndexer[FreeIndex];

		// Clear the bullet's variables because they can continue 
		// values stored from the last use of this bullet
		BulletPool[PoolIndex].ResetToDefaults();

		BulletPool[PoolIndex] = Definition;

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
			const int PoolIndex = BulletIndexer[Index];
			PapercraftBulletBehavior* Behavior = Behaviors[BulletPool[PoolIndex].Behavior];

			if(!Behavior->IsBulletOffScreen(BulletPool[PoolIndex]))
			{
				Behavior->TickBullet(DeltaTime, BulletPool[PoolIndex]);
			}
			else
			{
				// When there's only one bullet and we're recycling it, there's nothing to swap
				if(FreeIndex > 1)
				{
					const int LastActiveIndex = FreeIndex - 1;

					// "Kill" the bullet by recycling it (swapping the back active bullet with the killed bullet)
					BulletIndexer[Index] = BulletIndexer[LastActiveIndex];
					BulletIndexer[LastActiveIndex] = PoolIndex;
				}

				// Update the free index after killing a bullet
				FreeIndex--;
			}
		}
	}
}

// EOF
