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
			//SharedData->Float(CMPID_X) = static_cast<float>(CE.GetHGE().System_GetState(HGE_SCREENWIDTH)) * 0.5f;
			//SharedData->Float(CMPID_Y) = static_cast<float>(CE.GetHGE().System_GetState(HGE_SCREENHEIGHT)) * 0.5f;
			Behaviors[BulletPool[Index].Behavior]->TickBullet(DeltaTime, BulletPool[Index]);
		}
	}
}

// EOF
