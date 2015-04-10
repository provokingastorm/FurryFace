#include "cheezepizza.h"
#include "enginesubsystem.h"

EngineSubsystem::EngineSubsystem()
	: HGEEngine(NULL)
	, bIsInitialized(false)
{
}

EngineSubsystem::~EngineSubsystem()
{
}

void EngineSubsystem::Initialize()
{
	HGEEngine = hgeCreate(HGE_VERSION);

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
}