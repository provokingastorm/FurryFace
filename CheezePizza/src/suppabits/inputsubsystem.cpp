#include "cheezepizza.h"
#include "inputsubsystem.h"
#include "inputconfig.h"
#include "cheezepizzaengine.h"
#include "debugutilities.h"

#define DEFAULT_EVENT_SIZE 20

void InputSubsystem::InitializeInternal()
{
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
}

void InputSubsystem::PushConfig(InputConfig& Config)
{
	if(CurrentConfigIndex < MAX_CONFIG_STACK)
	{
		CurrentConfigIndex++;
		ConfigStack[CurrentConfigIndex] = &Config;
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
	}
}

void InputSubsystem::Tick(float DeltaTime)
{
	InputConfig* CurrentConfig = GetCurrentConfig();
	if(CurrentConfig != NULL)
	{ 
		CurrentConfig->HandleInput(DeltaTime);
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