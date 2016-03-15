#ifndef CollisionSubsystem_H_
#define CollisionSubsystem_H_

#ifndef EngineSubsystem_H_
#include "enginesubsystem.h"
#endif


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

	int AddCollisionComponent(class CollisionComponent* InComponent);
	bool RemoveCollisionComponent(int InID);

	void CheckForCollisions(float DeltaTime);

protected:

	// --------------------------------------------------------
	//	EngineSubsystem inherited protected methods

	void InitializeInternal();
	void ShutdownInternal();

private:

	static int NextCollisionID;
};

#endif

// EOF
