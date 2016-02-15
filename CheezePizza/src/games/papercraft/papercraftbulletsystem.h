#ifndef PapercraftBulletSystem_H_
#define PapercraftBulletSystem_H_

#ifndef PapercraftBulletBehaviors_H_
#include "papercraftbulletbehaviors.h"
#endif

// ----------------------------------------------------------------------------
// PapercraftBulletSystem - Defines
// ----------------------------------------------------------------------------

#define MAX_BULLETS		50


// ----------------------------------------------------------------------------
// PapercraftBulletSystem - Declaration
// ----------------------------------------------------------------------------

class PapercraftBulletSystem
{
public:
	inline static PapercraftBulletSystem& Instance();

	bool SpawnBullet(Bullet& Definition);
	inline bool CanSpawnBullet() const;

	void Tick(float DeltaTime);

private:
	PapercraftBulletSystem();
	~PapercraftBulletSystem();
	PapercraftBulletSystem(const PapercraftBulletSystem&);
	PapercraftBulletSystem& operator=(const PapercraftBulletSystem&);

	PapercraftBulletBehavior* Behaviors[BBT_Max];

	int BulletIndexer[MAX_BULLETS];
	Bullet BulletPool[MAX_BULLETS];

	int FreeIndex;
};


// ----------------------------------------------------------------------------
// PapercraftBulletSystem - Inline Functions
// ----------------------------------------------------------------------------

PapercraftBulletSystem& PapercraftBulletSystem::Instance()
{
	static PapercraftBulletSystem SubInstance;
	return SubInstance;
}

bool PapercraftBulletSystem::CanSpawnBullet() const
{
	return FreeIndex >= 0 && FreeIndex < (MAX_BULLETS-1);
}

#endif


// EOF
