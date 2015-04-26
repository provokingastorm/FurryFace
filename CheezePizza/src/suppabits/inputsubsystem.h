#ifndef InputSubsystem_H_
#define InputSubsystem_H_

#ifndef EngineSubsystem_H_
#include "enginesubsystem.h"
#endif

#ifndef Vector_STL_H_
#define Vector_STL_H_
#include <vector>
#endif

class InputSubsystem : public EngineSubsystem
{
public:
	DECLARE_SUBSYSTEM(InputSubsystem);
	~InputSubsystem();

	void PushConfig(class InputConfig& Config);
	void PopConfig(class InputConfig& Config);

	void HandleInput();

protected:
	void InitializeInternal();
	void ShutdownInternal();

private:
	void ClearCurrentConfig();
	void AssignLastConfig();
	class InputConfig* GetCurrentConfig();

	std::vector<class InputConfig*> ConfigStack;

	std::vector<int> KeyUpEvents;
	std::vector<int> KeyDownEvents;
};

#endif