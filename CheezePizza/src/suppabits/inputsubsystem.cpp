#include "cheezepizza.h"
#include "inputsubsystem.h"
#include "inputconfig.h"
#include "debugutilities.h"

#define DEFAULT_EVENT_SIZE 20

InputSubsystem::InputSubsystem()
{
	KeyUpEvents.reserve(DEFAULT_EVENT_SIZE);
	KeyDownEvents.reserve(DEFAULT_EVENT_SIZE);
}

InputSubsystem::~InputSubsystem()
{
}

void InputSubsystem::InitializeInternal()
{
}

void InputSubsystem::ShutdownInternal()
{
	while(ConfigStack.size() > 0)
	{
		delete ConfigStack[ConfigStack.size()-1];
		ConfigStack.pop_back();
	}

	ConfigStack.clear();
}

void InputSubsystem::PushConfig(InputConfig* Config)
{
	CPAssert(Config != NULL, "Passed an invalid InputConfig to the InputSubsystem");

	if(Config != NULL)
	{
		ClearCurrentConfig();

		ConfigStack.push_back(Config);
		AssignLastConfig();
	}
}

void InputSubsystem::PopConfig(InputConfig* Config)
{
	ConfigStack.pop_back();
	AssignLastConfig();
}

void InputSubsystem::ClearCurrentConfig()
{
	KeyUpEvents.clear();
	KeyUpEvents.reserve(DEFAULT_EVENT_SIZE);

	KeyDownEvents.clear();
	KeyDownEvents.reserve(DEFAULT_EVENT_SIZE);
}

void InputSubsystem::AssignLastConfig()
{
	ClearCurrentConfig();

	InputConfig* CurrentConfig = GetCurrentConfig();
	if(CurrentConfig != NULL)
	{
		CurrentConfig->GetKeyUpEvents(KeyUpEvents);
		CurrentConfig->GetKeyDownEvents(KeyUpEvents);
	}
}

void InputSubsystem::HandleInput()
{
	InputConfig* CurrentConfig = GetCurrentConfig();
	if(CurrentConfig != NULL)
	{ 
		const int KeyUpSize = KeyUpEvents.size();
		for(int i = 0; i < KeyUpSize; ++i)
		{
			if(HGEEngine->Input_KeyUp(KeyUpEvents[i]))
			{
				CurrentConfig->OnKeyUp(KeyUpEvents[i]);
			}
		}
	}
}

InputConfig* InputSubsystem::GetCurrentConfig()
{
	InputConfig* CurrentConfig = NULL;

	const int ConfigSize = ConfigStack.size();
	if(ConfigSize > 0)
	{
		CurrentConfig = ConfigStack[ConfigSize-1];
	}

	return CurrentConfig;
}