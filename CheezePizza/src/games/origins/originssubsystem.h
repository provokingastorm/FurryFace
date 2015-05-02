#ifndef OriginsSubsystem_H_
#define OriginsSubsystem_H_

#ifndef EngineSubsystem_H_
#include "enginesubsystem.h"
#endif

// ----------------------------------------------------------------------------
// OriginsSubsystem - Declaration
// ----------------------------------------------------------------------------

class OriginsSubsystem : public EngineSubsystem
{
public:
	DECLARE_SUBSYSTEM(OriginsSubsystem);

	// --------------------------------------------------------
	//	EngineSubsystem inherited methods

	void InitializeGameEngine(class IPlatform& Platform);

protected:

	// --------------------------------------------------------
	//	EngineSubsystem inherited methods

	void InitializeInternal();
	void ShutdownInternal();

private:
};

#endif