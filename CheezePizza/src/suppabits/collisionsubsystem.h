#ifndef CollisionSubsystem_H_
#define CollisionSubsystem_H_

#ifndef EngineSubsystem_H_
#include "enginesubsystem.h"
#endif

#ifndef CollisionComponent_H_
#include "collisioncomponent.h"
#endif


// ----------------------------------------------------------------------------
// CollisionSubsystem - Defines
// ----------------------------------------------------------------------------

#define	MAX_COLLISION_COMPONENTS	50

// ----------------------------------------------------------------------------
// CollisionSubsystem - Declaration
// ----------------------------------------------------------------------------

class CollisionSubsystem : public EngineSubsystem
{
public:

	DECLARE_SUBSYSTEM(CollisionSubsystem);

	// --------------------------------------------------------
	//	EngineSubsystem inherited public methods

	void Tick(float DeltaTime);

	// --------------------------------------------------------
	//	CollisionSubsystem registration public methods

	CollisionComponent* CreateCollisionComponent();
	bool RemoveCollisionComponent(CollisionComponent* InComponent);

	void CheckForCollisions(float DeltaTime);

protected:

	// --------------------------------------------------------
	//	EngineSubsystem inherited protected methods

	void InitializeInternal();
	void ShutdownInternal();

private:

	CollisionComponent Components[MAX_COLLISION_COMPONENTS];
	int FirstFreeCompIndex;
};

#endif

// EOF
