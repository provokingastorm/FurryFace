#include "enginesubsystem.h"
#include "cheezepizzaengine.h"
#include "win32platform.h"
#include "..\..\include\hge.h"

#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


extern EngineSubsystem& GetGameSubsystem();

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
