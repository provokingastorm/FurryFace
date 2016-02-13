#ifndef PapercraftSubsystem_H_
#define PapercraftSubsystem_H_

#ifndef EngineSubsystem_H_
#include "enginesubsystem.h"
#endif

// ----------------------------------------------------------------------------
// PapercraftSubsystem - Declaration
// ----------------------------------------------------------------------------

class PapercraftSubsystem : public EngineSubsystem
{
public:
	DECLARE_SUBSYSTEM(PapercraftSubsystem);

	// --------------------------------------------------------
	//	EngineSubsystem inherited methods

	void InitializeGameEngine(class IPlatform& Platform);

	class PapercraftBulletSystem* BulletSystem;

protected:

	// --------------------------------------------------------
	//	EngineSubsystem inherited methods

	void InitializeInternal();
	void ShutdownInternal();

private:
};

#endif

// EOF
