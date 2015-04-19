#include "cheezepizza.h"
#include "gamesession.h"
#include "cheezepizzaengine.h"


GameSession::GameSession()
	: HGEEngine(NULL)
	, bGameOver(false)
	, bPaused(false)
{
}


GameSession::~GameSession()
{
}

void GameSession::Initialize()
{
	if(HGEEngine == NULL)
	{
		HGEEngine = hgeCreate(HGE_VERSION);
	}

	CheezePizzaEngine& CE = CheezePizzaEngine::Instance();

	// First, initialize the engine
	CE.Initialize(GetGameName(), GetGameShortName());

	// Then, provide any game-specific configuration
	PreInit();
}

void GameSession::Startup()
{
	LoadGame();

	CheezePizzaEngine::Instance().Startup();

	// NOTE: Do not add any code after System_Start(). All other code must be handled by the HGE callbacks (Tick, Render, etc)
}

void GameSession::Shutdown()
{
	ShutdownInernal();

	CheezePizzaEngine::Instance().Shutdown();

	if(HGEEngine != NULL)
	{
		HGEEngine->Release();
		HGEEngine = NULL;
	}
}

bool GameSession::RouteEngineEvent(EEngineEvent Event)
{
	bool EngineResponse = false;

	switch (Event)
	{
	case EE_Tick:
		EngineResponse = (bGameOver) ? true : CheezePizzaEngine::Instance().Tick();
		break;

	case EE_Render:
		CheezePizzaEngine::Instance().Render();
		EngineResponse = false;
		break;

	case EE_Exit:
		EngineResponse = true;
		break;

	case EE_FocusGained:
		CheezePizzaEngine::Instance().OnFocusGained();
		EngineResponse = false;
		break;

	case EE_FocusLost:
		CheezePizzaEngine::Instance().OnFocusLost();
		EngineResponse = false;
		break;

	default:
		break;
	}

	return EngineResponse;
}

void GameSession::Pause()
{
	bPaused = true;
}