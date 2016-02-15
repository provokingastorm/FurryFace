#include "cheezepizza.h"
#include "cheezepizzaengine.h"
#include "enginesubsystem.h"
#include "tickable.h"
#include "irenderable.h"
#include "iplatform.h"
#include "hgeresource.h"

// ----------------------------------------------------------------------------
// HGE - Defines
// ----------------------------------------------------------------------------

#define GAME_NAME_LENGTH		48
#define GAME_NAME_SHORT_LENGTH	8


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
// CheezePizzaEngine - Definition
// ----------------------------------------------------------------------------

CheezePizzaEngine::CheezePizzaEngine()
	: PlatformInterface(NULL)
	, ResourceManager(NULL)
	, bIsHGEInitialized(false)
	, bExitApplication(false)
	, bTickedOnce(false)
	, GameName(NULL)
	, GameShortName(NULL)
	, ScreenWidth(640)
	, ScreenHeight(480)
{
}

CheezePizzaEngine::~CheezePizzaEngine()
{
}

void CheezePizzaEngine::Initialize(class IPlatform& Platform, char* InGameName, char* InGameShortName)
{
	CPAssert(bIsHGEInitialized == false, "Trying to initialize an already initialized engine");
	PlatformInterface = &Platform;

	GameName = InGameName;
	GameShortName = ChzStrLower(InGameShortName);

	if(HasPlatformEngine() && !bIsHGEInitialized)
	{
		HGE& HGERef = GetHGE();

		// Setup the log file
		char LogFilename[128];
		sprintf(LogFilename, "logs/%s.log", GameShortName);
		HGERef.System_SetState(HGE_LOGFILE, LogFilename);

		HGERef.System_SetState(HGE_SHOWSPLASH, true);
		HGERef.System_SetState(HGE_FPS, 60);
		HGERef.System_SetState(HGE_TITLE, GameName);

		// Disable Sound otherwise game crashes without bass.dll
		HGERef.System_SetState(HGE_USESOUND, false);

		ImportEngineConfig();

		// Set the resource manager
		char ResourceFilename[128];
		sprintf(ResourceFilename, "%s/res/%sgame.res", GameShortName, GameShortName);
		ResourceManager = new hgeResourceManager(ResourceFilename);
		ResourceManager->Precache(RG_AlwaysLoaded);

		HGERef.System_SetState(HGE_FRAMEFUNC, FrameFunc);
		HGERef.System_SetState(HGE_RENDERFUNC, RenderFunc);
		HGERef.System_SetState(HGE_FOCUSLOSTFUNC, FocusLostFunc);
		HGERef.System_SetState(HGE_FOCUSGAINFUNC, FocusGainedFunc);
		HGERef.System_SetState(HGE_EXITFUNC, ExitFunc);

		bIsHGEInitialized = HGERef.System_Initiate();
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

	if(HasPlatformEngine())
	{
		// Restore video mode and free all allocated resources
		GetHGE().System_Shutdown();
	}
}

void CheezePizzaEngine::Startup()
{
	if(HasPlatformEngine())
	{
		if(bIsHGEInitialized)
		{
			GetHGE().System_Start();

			// NOTE: Do not add any code after System_Start(). All other code must be handled by the HGE callbacks (Tick, Render, etc)
		}
		else
		{	
			// If HGE initialization failed show error message
			MessageBox(NULL, GetHGE().System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
		}
	}
}

bool CheezePizzaEngine::Tick()
{
	if(!IsExiting())
	{
		float DeltaTime = GetHGE().Timer_GetDelta();

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
	HGE& HGERef = GetHGE();
	HGERef.Gfx_BeginScene();
	HGERef.Gfx_Clear(0);

	// Render each object sequentially. Assumes that the client managed 
	// the render order when adding objects to the render queue.
	const int NumRenderables = RenderQueue.size();
	for(int i = 0; i < NumRenderables; ++i)
	{
		RenderQueue[i]->Render(HGERef);
	}

	HGERef.Gfx_EndScene();

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
	HGE& HGERef = GetHGE();
	HGERef.System_SetState(HGE_INIFILE, "config/cheezepizzaengine.ini");

	ScreenWidth = HGERef.Ini_GetInt("DisplayOptions", "ScreenWidth", ScreenWidth);
	ScreenHeight = HGERef.Ini_GetInt("DisplayOptions", "ScreenHeight", ScreenHeight);
	int ColorDepth = HGERef.Ini_GetInt("DisplayOptions", "ColorDepth", 32);
	int FullscreenMode = HGERef.Ini_GetInt("DisplayOptions", "FullscreenMode", 0);

	HGERef.System_SetState(HGE_SCREENWIDTH, ScreenWidth);
	HGERef.System_SetState(HGE_SCREENHEIGHT, ScreenHeight);
	HGERef.System_SetState(HGE_SCREENBPP, ColorDepth);

	if(!FullscreenMode)
	{
		HGERef.System_SetState(HGE_WINDOWED, true);
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

bool CheezePizzaEngine::HasPlatformEngine() const
{
	return (PlatformInterface != NULL && PlatformInterface->GetHGE() != NULL);
}

IPlatform& CheezePizzaEngine::GetPlatform() const
{
	return *(PlatformInterface);
}

HGE&  CheezePizzaEngine::GetHGE() const
{
	return *(GetPlatform().GetHGE());
}

bool CheezePizzaEngine::IsInitialized() const
{
	return (HasPlatformEngine() && bIsHGEInitialized && ResourceManager != NULL);
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

// EOF
