#include "cheezepizza.h"

// Papercraft
#include "papercraftsubsystem.h"
#include "papercraftplayerfactory.h"
#include "papercraftplayer.h"
#include "papercraftgameconfig.h"

// Subsystems
#include "world2d.h"
#include "playersubsystem.h"
#include "inputsubsystem.h"

// Base engine
#include "cheezepizzaengine.h"
#include "iplatform.h"

// ----------------------------------------------------------------------------
// Global function for the Cheeze Pizza Engine
// ----------------------------------------------------------------------------

IMPLEMENT_GAME_SUBSYSTEM_CREATOR(PapercraftSubsystem);

// ----------------------------------------------------------------------------
// PapercraftPlayerCreated - Definition
// ----------------------------------------------------------------------------

struct PapercraftPlayerCreated : public DelegatePlayer
{
	void Invoke(class LocalPlayer& Player, ELocalPlayerIndex PlayerIndex)
	{
		PapercraftPlayer& PapercraftLocalPlayer = static_cast<PapercraftPlayer&>(Player);

		PapercraftGameConfig& PapercraftInput = *(new PapercraftGameConfig(PapercraftLocalPlayer));
		InputSubsystem::Instance().PushConfig(PapercraftInput);
	}
};

// ----------------------------------------------------------------------------
// PapercraftSubsystem - Definition
// ----------------------------------------------------------------------------

void PapercraftSubsystem::InitializeGameEngine(class IPlatform& Platform)
{
	CheezePizzaEngine& CE = CheezePizzaEngine::Instance();

	CE.Initialize(Platform, "Papercraft", "Papercraft");

	CE.AddEngineSubsystem(InputSubsystem::Instance());
	CE.AddEngineSubsystem(PlayerSubsystem::Instance());
	CE.AddEngineSubsystem(World2D::Instance());
	CE.AddEngineSubsystem(*this);
}

void PapercraftSubsystem::InitializeInternal()
{
	// Provide the engine with a factory that will create Papercraft-specific players
	PapercraftPlayerFactory& Factory = *(new PapercraftPlayerFactory());
	PlayerSubsystem::Instance().SetPlayerFactory(Factory);

	PapercraftPlayerCreated& CreationDelegate = *(new PapercraftPlayerCreated());
	PlayerSubsystem::Instance().AddPlayerCreatedDelegate(CreationDelegate);
}

void PapercraftSubsystem::ShutdownInternal()
{
}

// EOF
