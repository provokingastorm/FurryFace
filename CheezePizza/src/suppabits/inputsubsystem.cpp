#include "cheezepizza.h"
#include "inputsubsystem.h"
#include "sharedinputconfigs.h"
#include "inputconfig.h"
#include "debugutilities.h"

#define DEFAULT_EVENT_SIZE 20

void InputSubsystem::InitializeInternal()
{
	KeyUpEvents.reserve(DEFAULT_EVENT_SIZE);
	KeyDownEvents.reserve(DEFAULT_EVENT_SIZE);

	CurrentConfigIndex = -1;

	for(int i = 0; i < MAX_CONFIG_STACK; i++)
	{
		ConfigStack[i] = NULL;
	}

	// Always provide one input config when running the game to catch basic stuff like closing the application.
	//DefaultEngineConfig& DefaultConfig = *(new DefaultEngineConfig());
	//PushConfig(DefaultConfig);
}

void InputSubsystem::ShutdownInternal()
{
	for(int i = 0; i < MAX_CONFIG_STACK; i++)
	{
		delete ConfigStack[i];
		ConfigStack[i] = NULL;
		CurrentConfigIndex--;
	}

	KeyDownEvents.~vector();
	KeyUpEvents.~vector();
}

void InputSubsystem::PushConfig(InputConfig& Config)
{
	if(CurrentConfigIndex < MAX_CONFIG_STACK)
	{
		CurrentConfigIndex++;
		ConfigStack[CurrentConfigIndex] = &Config;
		AssignLastConfig();
	}
}

void InputSubsystem::PopConfig(InputConfig& Config)
{
	// Pop the current input config only if it matches the current input config
	if(CurrentConfigIndex >= 0 && ConfigStack[CurrentConfigIndex] == &Config)
	{
		delete ConfigStack[CurrentConfigIndex];
		ConfigStack[CurrentConfigIndex] = NULL;
		CurrentConfigIndex--;

		AssignLastConfig();
	}
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
		CurrentConfig->GetKeyDownEvents(KeyDownEvents);
		CurrentConfig->GetKeyUpEvents(KeyUpEvents);
	}
}

void InputSubsystem::Tick(float DeltaTime)
{
	InputConfig* CurrentConfig = GetCurrentConfig();
	if(CurrentConfig != NULL)
	{ 
		CurrentConfig->SetDeltaTime(DeltaTime);

		const int KeyDownSize = KeyDownEvents.size();
		for(int j = 0; j < KeyDownSize; ++j)
		{
			if(HGEEngine->Input_GetKeyState(KeyDownEvents[j]))
			{
				CurrentConfig->OnKeyDown(KeyDownEvents[j]);
			}
		}

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

	if(CurrentConfigIndex >= 0)
	{
		CurrentConfig = ConfigStack[CurrentConfigIndex];
	}

	return CurrentConfig;
}