#include "cheezepizza.h"
#include "cheezepizzaengine.h"
#include "enginesubsystem.h"
#include "tickable.h"
#include "irenderable.h"
#include "hgeresource.h"

#define GAME_NAME_LENGTH		48
#define GAME_NAME_SHORT_LENGTH	8

CheezePizzaEngine::CheezePizzaEngine()
	: HGEEngine(NULL)
	, ResourceManager(NULL)
	, bIsHGEInitialized(false)
	, bExitApplication(false)
	, bTickedOnce(false)
	, GameName(NULL)
	, GameShortName(NULL)
{
}

CheezePizzaEngine::~CheezePizzaEngine()
{
}

void CheezePizzaEngine::Initialize(char* InGameName, char* InGameShortName)
{
	CPAssert(bIsHGEInitialized == false, "Trying to initialize an already initialized engine");
	HGEEngine = hgeCreate(HGE_VERSION);

	GameName = InGameName;
	GameShortName = ChzStrLower(InGameShortName);

	if(HGEEngine != NULL && !bIsHGEInitialized)
	{
		// Setup the log file
		char LogFilename[128];
		sprintf(LogFilename, "logs/%s.log", GameShortName);
		HGEEngine->System_SetState(HGE_LOGFILE, LogFilename);

		HGEEngine->System_SetState(HGE_SHOWSPLASH, true);
		HGEEngine->System_SetState(HGE_FPS, 60);
		HGEEngine->System_SetState(HGE_TITLE, GameName);

		// Disable Sound otherwise game crashes without bass.dll
		HGEEngine->System_SetState(HGE_USESOUND, false);

		ImportEngineConfig();

		// Set the resource manager
		char ResourceFilename[128];
		sprintf(ResourceFilename, "%s/res/%sgame.res", GameShortName, GameShortName);
		ResourceManager = new hgeResourceManager(ResourceFilename);
		ResourceManager->Precache(RG_AlwaysLoaded);

		bIsHGEInitialized = HGEEngine->System_Initiate();
	}
}

void CheezePizzaEngine::Shutdown()
{
	// No need to delete render queue items. It's temp
	RenderQueue.~vector();

	SAFE_DELETE_ARRAY(GameShortName);

	const unsigned int NumSubsystems = Subsystems.size();
	for(unsigned int j = 0; j < NumSubsystems; ++j)
	{
		SAFE_SHUTDOWN(Subsystems[j]);
	}
	Subsystems.~vector();

	// Delete all loaded resources
	if(ResourceManager != NULL)
	{
		ResourceManager->Purge();
		SAFE_DELETE(ResourceManager);
	}

	if(HGEEngine != NULL)
	{
		// Restore video mode and free all allocated resources
		HGEEngine->System_Shutdown();

		// If there are no more references, the HGE object will be deleted.
		HGEEngine->Release();
		HGEEngine = NULL;
	}
}

void CheezePizzaEngine::Startup()
{
	if(HGEEngine != NULL)
	{
		if(bIsHGEInitialized)
		{
			HGEEngine->System_Start();

			// NOTE: Do not add any code after System_Start(). All other code must be handled by the HGE callbacks (Tick, Render, etc)
		}
		else
		{	
			// If HGE initialization failed show error message
			MessageBox(NULL, HGEEngine->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
		}
	}
}

bool CheezePizzaEngine::Tick()
{
	if(!IsExiting())
	{
		float DeltaTime = HGEEngine->Timer_GetDelta();

		if(!bTickedOnce)
		{
			bTickedOnce = true;
			OnFirstTick(DeltaTime);
		}

		for(unsigned int i = 0; i < Subsystems.size(); ++i)
		{
			Subsystems[i]->Tick(DeltaTime);
		}
	}

	return IsExiting();
}

void CheezePizzaEngine::Render()
{
	HGE& HGERef = *HGEEngine;
	HGERef.Gfx_BeginScene();
	HGERef.Gfx_Clear(0);

	// Render each object sequentially. Assumes that the client managed 
	// the render order when adding objects to the render queue.
	const int NumRenderables = RenderQueue.size();
	for(int j = 0; j < NumRenderables; ++j)
	{
		RenderQueue[j]->Render(HGERef);
	}

	HGEEngine->Gfx_EndScene();

	// Clear the render queue so that we don't draw unwanted graphics
	RenderQueue.clear();
}

void CheezePizzaEngine::OnFocusGained()
{
	const int NumSubsystem = Subsystems.size();
	for(int i = 0; i < NumSubsystem; ++i)
	{
		Subsystems[i]->OnAppFocusGained();
	}
}

void CheezePizzaEngine::OnFocusLost()
{
	const int NumSubsystem = Subsystems.size();
	for(int i = 0; i < NumSubsystem; ++i)
	{
		Subsystems[i]->OnAppFocusLost();
	}
}

void CheezePizzaEngine::ImportEngineConfig()
{
	CPAssert(HGEEngine != NULL, "Engine not initialized");

	HGEEngine->System_SetState(HGE_INIFILE, "config/cheezepizzaengine.ini");

	int ScreenWidth = HGEEngine->Ini_GetInt("DisplayOptions", "ScreenWidth", 640);
	int ScreenHeight = HGEEngine->Ini_GetInt("DisplayOptions", "ScreenHeight", 480);
	int ColorDepth = HGEEngine->Ini_GetInt("DisplayOptions", "ColorDepth", 32);
	int FullscreenMode = HGEEngine->Ini_GetInt("DisplayOptions", "FullscreenMode", 0);

	HGEEngine->System_SetState(HGE_SCREENWIDTH, ScreenWidth);
	HGEEngine->System_SetState(HGE_SCREENHEIGHT, ScreenHeight);
	HGEEngine->System_SetState(HGE_SCREENBPP, ColorDepth);

	if(!FullscreenMode)
	{
		HGEEngine->System_SetState(HGE_WINDOWED, true);
	}
}

void CheezePizzaEngine::OnFirstTick(float DeltaTime)
{
	const int NumSubsystem = Subsystems.size();
	for(int i = 0; i < NumSubsystem; ++i)
	{
		Subsystems[i]->OnFirstEngineTick();
	}
}

bool CheezePizzaEngine::IsInitialized() const
{
	return (HGEEngine != NULL && bIsHGEInitialized && ResourceManager != NULL);
}

bool CheezePizzaEngine::IsExiting() const
{
	return bExitApplication;
}

void CheezePizzaEngine::ExitApplication()
{
	bExitApplication = true;
}

bool CheezePizzaEngine::AddEngineSubsystem(EngineSubsystem& Subsystem)
{
	bool bAlreadyTracked = false; 
	bool bAdded = false;
	
	const int NumSubsystems = Subsystems.size();
	for(int i = 0; i < NumSubsystems; ++i)
	{
		if(Subsystems[i] == &Subsystem)
		{
			bAlreadyTracked = true;
			break;
		}
	}

	if(!bAlreadyTracked)
	{
		if(!Subsystem.IsInitialized())
		{
			Subsystem.Initialize();
		}

		Subsystems.push_back(&Subsystem);
		bAdded = true;
	}

	return bAdded;
}

// Returns true if the object was added to the render queue; false, otherwise.
bool CheezePizzaEngine::AddToRenderQueue(IRenderable& RenderableObject)
{
	RenderQueue.push_back(&RenderableObject);
	return true;
}

void CheezePizzaEngine::SetGameNames(char* InGameName, char* InGameShortName)
{
	GameName = InGameName;
	GameShortName = ChzStrLower(InGameShortName);

	// Setup the log file
	char LogFilename[128];
	sprintf(LogFilename, "logs/%s.log", GameShortName);
	HGEEngine->System_SetState(HGE_LOGFILE, LogFilename);

	HGEEngine->System_SetState(HGE_TITLE, GameName);
}

// EOF
