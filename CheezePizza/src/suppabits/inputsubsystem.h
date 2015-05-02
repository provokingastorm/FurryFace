#ifndef InputSubsystem_H_
#define InputSubsystem_H_

#ifndef EngineSubsystem_H_
#include "enginesubsystem.h"
#endif

#ifndef Vector_STL_H_
#define Vector_STL_H_
#include <vector>
#endif

// ----------------------------------------------------------------------------
// InputSubsystem - Defines
// ----------------------------------------------------------------------------

#define MAX_CONFIG_STACK	4

class InputSubsystem : public EngineSubsystem
{
public:
	DECLARE_SUBSYSTEM(InputSubsystem);

	// --------------------------------------------------------
	//	InputConfig Methods

	void PushConfig(class InputConfig& Config);
	void PopConfig(class InputConfig& Config);

	void HandleInput();

protected:

	// --------------------------------------------------------
	//	EngineSubsystem inherited methods

	void InitializeInternal();
	void ShutdownInternal();
	void Tick(float DeltaTime);

private:

	// --------------------------------------------------------
	// InputConfig private methods

	void ClearCurrentConfig();
	void AssignLastConfig();
	class InputConfig* GetCurrentConfig();

	class InputConfig* ConfigStack[MAX_CONFIG_STACK];
	int CurrentConfigIndex;

	std::vector<int> KeyUpEvents;
	std::vector<int> KeyDownEvents;
};

#endif