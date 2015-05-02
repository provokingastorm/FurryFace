#include "enginesubsystem.h"
#include "cheezepizzaengine.h"
#include "..\..\include\hge.h"

#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


extern EngineSubsystem& GetGameSubsystem();
HGE* HGEEngine = NULL;


// ----------------------------------------------------------------------------
// HGE - Callbacks
// ----------------------------------------------------------------------------

bool FrameFunc()
{
	return CheezePizzaEngine::Instance().Tick();
}

bool RenderFunc()
{
	CheezePizzaEngine::Instance().Render();
	return false;
}

bool FocusLostFunc()
{
	CheezePizzaEngine::Instance().OnFocusLost();
	return false;
}

bool FocusGainedFunc()
{
	CheezePizzaEngine::Instance().OnFocusGained();
	return false;
}

bool ExitFunc()
{
	return true;
}

// ----------------------------------------------------------------------------
// WinMain
// ----------------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	EngineSubsystem& Subsystem = GetGameSubsystem();

	// Initialize the game engine
	HGEEngine = hgeCreate(HGE_VERSION);
	Subsystem.InitializeGameEngine();

	if(HGEEngine != NULL)
	{
		HGEEngine->System_SetState(HGE_FRAMEFUNC, FrameFunc);
		HGEEngine->System_SetState(HGE_RENDERFUNC, RenderFunc);
		HGEEngine->System_SetState(HGE_FOCUSLOSTFUNC, FocusLostFunc);
		HGEEngine->System_SetState(HGE_FOCUSGAINFUNC, FocusGainedFunc);
		HGEEngine->System_SetState(HGE_EXITFUNC, ExitFunc);

		// Now, run the game
		CheezePizzaEngine::Instance().Startup();
	}

	// At this point, the player exited the application in the game-specific way
	CheezePizzaEngine::Instance().Shutdown();

	if(HGEEngine != NULL)
	{
		HGEEngine->Release();
		HGEEngine = NULL;
	}

	// Dump memory leaks
#if defined(_DEBUG)
	_CrtDumpMemoryLeaks();
#endif

	return 0;
}
