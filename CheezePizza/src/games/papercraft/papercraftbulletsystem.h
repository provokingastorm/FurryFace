#ifndef PapercraftBulletSystem_H_
#define PapercraftBulletSystem_H_

#ifndef EngineSubsystem_H_
#include "enginesubsystem.h"
#endif

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

class PapercraftBulletSystem : public EngineSubsystem
{
public:
	DECLARE_SUBSYSTEM(PapercraftBulletSystem);

	bool SpawnBullet(Bullet& Definition);
	inline bool CanSpawnBullet() const;

	// --------------------------------------------------------
	//	EngineSubsystem inherited public methods

	void Tick(float DeltaTime);

protected:

	// --------------------------------------------------------
	//	EngineSubsystem inherited protected methods

	void InitializeInternal();
	void ShutdownInternal();

private:
	
	PapercraftBulletBehavior* Behaviors[BBT_Max];

	int BulletIndexer[MAX_BULLETS];
	Bullet BulletPool[MAX_BULLETS];

	int FreeIndex;
};


// ----------------------------------------------------------------------------
// PapercraftBulletSystem - Inline Functions
// ----------------------------------------------------------------------------

bool PapercraftBulletSystem::CanSpawnBullet() const
{
	return FreeIndex >= 0 && FreeIndex < (MAX_BULLETS-1);
}

#endif


// EOF
