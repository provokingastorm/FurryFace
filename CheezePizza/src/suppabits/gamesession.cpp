#include "cheezepizza.h"
#include "gamesession.h"
#include "cheezepizzaengine.h"


GameSession::GameSession()
	: CheezeEngine(NULL)
	, HGEEngine(NULL)
	, bGameOver(false)
	, bPaused(false)
{
}


GameSession::~GameSession()
{
}

void GameSession::Initialize()
{
	CPAssert(CheezeEngine == NULL, "Trying to initialize the engine again!");

	if(HGEEngine == NULL)
	{
		HGEEngine = hgeCreate(HGE_VERSION);
	}

	if(CheezeEngine == NULL)
	{
		CheezeEngine = &CheezePizzaEngine::Instance();

		// First, initialize the engine
		CheezeEngine->Initialize(GetGameName(), GetGameShortName());
		//CheezeEngine->SetFirstTickCallback()

		// Then, provide any game-specific configuration
		PreInit();
	}
}

void GameSession::Startup()
{
	if(CheezeEngine != NULL)
	{
		LoadGame();

		CheezeEngine->Startup();

		// NOTE: Do not add any code after System_Start(). All other code must be handled by the HGE callbacks (Tick, Render, etc)
	}
}

void GameSession::Shutdown()
{
	ShutdownInernal();

	if(CheezeEngine != NULL)
	{
		CheezeEngine->Shutdown();
		delete CheezeEngine;
	}

	if(HGEEngine != NULL)
	{
		HGEEngine->Release();
		HGEEngine = NULL;
	}
}

bool GameSession::RouteEngineEvent(EEngineEvent Event)
{
	bool EngineResponse = false;

	if(CheezeEngine != NULL)
	{
		switch (Event)
		{
		case EE_Tick:
			EngineResponse = (bGameOver) ? true : CheezeEngine->Tick();
			break;

		case EE_Render:
			CheezeEngine->Render();
			EngineResponse = false;
			break;

		case EE_Exit:
			EngineResponse = true;
			break;

		case EE_FocusGained:
			CheezeEngine->OnFocusGained();
			EngineResponse = false;
			break;

		case EE_FocusLost:
			CheezeEngine->OnFocusLost();
			EngineResponse = false;
			break;

		default:
			break;
		}
	}

	return EngineResponse;
}

void GameSession::Pause()
{
	bPaused = true;
}