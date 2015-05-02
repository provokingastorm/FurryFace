#include "enginesubsystem.h"
#include "cheezepizzaengine.h"
#include "win32platform.h"
#include "..\..\include\hge.h"

#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


extern EngineSubsystem& GetGameSubsystem();


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
	Win32Platform& PlatformInterface = *(new Win32Platform());
	Subsystem.InitializeGameEngine(PlatformInterface);

	if(PlatformInterface.GetHGE() != NULL)
	{
		PlatformInterface.GetHGE()->System_SetState(HGE_FRAMEFUNC, FrameFunc);
		PlatformInterface.GetHGE()->System_SetState(HGE_RENDERFUNC, RenderFunc);
		PlatformInterface.GetHGE()->System_SetState(HGE_FOCUSLOSTFUNC, FocusLostFunc);
		PlatformInterface.GetHGE()->System_SetState(HGE_FOCUSGAINFUNC, FocusGainedFunc);
		PlatformInterface.GetHGE()->System_SetState(HGE_EXITFUNC, ExitFunc);

		// Now, run the game
		CheezePizzaEngine::Instance().Startup();
	}

	// At this point, the player exited the application in the game-specific way
	CheezePizzaEngine::Instance().Shutdown();

	delete (&PlatformInterface);

	// Dump memory leaks
#if defined(_DEBUG)
	_CrtDumpMemoryLeaks();
#endif

	return 0;
}
