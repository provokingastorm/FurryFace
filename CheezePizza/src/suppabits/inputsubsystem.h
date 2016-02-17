#ifndef InputSubsystem_H_
#define InputSubsystem_H_

#ifndef EngineSubsystem_H_
#include "enginesubsystem.h"
#endif

// ----------------------------------------------------------------------------
// InputSubsystem - Defines
// ----------------------------------------------------------------------------

#define MAX_CONFIG_STACK	4

// ----------------------------------------------------------------------------
// InputSubsystem - Declaration
// ----------------------------------------------------------------------------

class InputSubsystem : public EngineSubsystem
{
public:
	DECLARE_SUBSYSTEM(InputSubsystem);

	// --------------------------------------------------------
	//	InputConfig Methods

	void PushConfig(class InputConfig& Config);
	void PopConfig(class InputConfig& Config);

	// --------------------------------------------------------
	//	EngineSubsystem inherited public methods

	void Tick(float DeltaTime);

protected:

	// --------------------------------------------------------
	//	EngineSubsystem inherited protected methods

	void InitializeInternal();
	void ShutdownInternal();

private:

	// --------------------------------------------------------
	// InputConfig private methods

	class InputConfig* GetCurrentConfig();

	class InputConfig* ConfigStack[MAX_CONFIG_STACK];
	int CurrentConfigIndex;
};

#endif

// EOF
