#include "gamesession.h"
#include "..\..\include\hge.h"

#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>



extern GameSession* CreateGameSession();
GameSession* Session = NULL;

////////////////////////////////////////////////
// HGE Callbacks
////////////////////////////////////////////////

bool FrameFunc()
{
	return Session->RouteEngineEvent(EE_Tick);
}

bool RenderFunc()
{
	return Session->RouteEngineEvent(EE_Render);
}

bool FocusLostFunc()
{
	return Session->RouteEngineEvent(EE_FocusLost);
}

bool FocusGainedFunc()
{
	return Session->RouteEngineEvent(EE_FocusGained);
}

bool ExitFunc()
{
	return Session->RouteEngineEvent(EE_Exit);
}

////////////////////////////////////////////////
// WinMain
////////////////////////////////////////////////

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Session = CreateGameSession();

	if(Session != NULL)
	{
		HGE* HGEEngine = hgeCreate(HGE_VERSION);
		Session->Initialize();

		if(HGEEngine != NULL)
		{
			HGEEngine->System_SetState(HGE_FRAMEFUNC, FrameFunc);
			HGEEngine->System_SetState(HGE_RENDERFUNC, RenderFunc);
			HGEEngine->System_SetState(HGE_FOCUSLOSTFUNC, FocusLostFunc);
			HGEEngine->System_SetState(HGE_FOCUSGAINFUNC, FocusGainedFunc);
			HGEEngine->System_SetState(HGE_EXITFUNC, ExitFunc);

			Session->Startup();
		}

		Session->Shutdown();

		if(HGEEngine != NULL)
		{
			HGEEngine->Release();
			HGEEngine = NULL;
		}

		delete Session;
	}

	// Dump memory leaks
#if defined(_DEBUG)
	_CrtDumpMemoryLeaks();
#endif

	return 0;
}
