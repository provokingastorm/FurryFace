#include "cheezepizza.h"
#include "enginesubsystem.h"

EngineSubsystem::EngineSubsystem()
	: HGEEngine(NULL)
	, bIsInitialized(false)
	, bTickedOnce(false)
{
}

EngineSubsystem::~EngineSubsystem()
{
}

void EngineSubsystem::Initialize()
{
	HGEEngine = hgeCreate(HGE_VERSION);
	bTickedOnce = false;

	InitializeInternal();
	bIsInitialized = true;
}

void EngineSubsystem::Shutdown()
{
	ShutdownInternal();

	if(HGEEngine != NULL)
	{
		HGEEngine->Release();
		HGEEngine = NULL;
	}

	bIsInitialized = false;
}

void EngineSubsystem::OnFirstEngineTick()
{
	bTickedOnce = true;
	FirstEngineTickInternal();
}