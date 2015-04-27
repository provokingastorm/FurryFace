#include "gamesession.h"
#include "cheezepizzaengine.h"
#include "..\..\include\hge.h"

#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


extern GameSession* CreateGameSession();
GameSession* Session = NULL;
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
	Session = CreateGameSession();

	if(Session != NULL)
	{
		// Initialize the game engine
		HGEEngine = hgeCreate(HGE_VERSION);
		CheezePizzaEngine::Instance().Initialize(Session->GetGameName(), Session->GetGameShortName());

		// Provides game-specific initialization
		Session->PreInit();

		if(HGEEngine != NULL)
		{
			HGEEngine->System_SetState(HGE_FRAMEFUNC, FrameFunc);
			HGEEngine->System_SetState(HGE_RENDERFUNC, RenderFunc);
			HGEEngine->System_SetState(HGE_FOCUSLOSTFUNC, FocusLostFunc);
			HGEEngine->System_SetState(HGE_FOCUSGAINFUNC, FocusGainedFunc);
			HGEEngine->System_SetState(HGE_EXITFUNC, ExitFunc);

			// After the engine is configured, load up starting assets
			Session->LoadGame();

			// Now, run the game
			CheezePizzaEngine::Instance().Startup();
		}

		// At this point, the player exited the application in the game-specific way
		delete Session;
		CheezePizzaEngine::Instance().Shutdown();

		if(HGEEngine != NULL)
		{
			HGEEngine->Release();
			HGEEngine = NULL;
		}
	}

	// Dump memory leaks
#if defined(_DEBUG)
	_CrtDumpMemoryLeaks();
#endif

	return 0;
}
