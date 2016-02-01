#include "cheezepizza.h"

// Papercraft
#include "papercraftcomponentdata.h"
#include "papercraftsubsystem.h"
#include "papercraftplayerfactory.h"
#include "papercraftplayer.h"
#include "papercraftgameconfig.h"

// Shared implementations
#include "sharedrenderables.h"
#include "sharedcomponents.h"

// Subsystems
#include "inputsubsystem.h"
#include "playersubsystem.h"
#include "world2d.h"
#include "inputsubsystem.h"
#include "componentsystem.h"

// Base engine
#include "scene2dobject.h"
#include "cheezepizzaengine.h"
#include "iplatform.h"
#include "hgeresource.h"

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
		CheezePizzaEngine& CE = CheezePizzaEngine::Instance();
		PapercraftPlayer& PapercraftLocalPlayer = static_cast<PapercraftPlayer&>(Player);
		PapercraftGameConfig& PapercraftInput = *(new PapercraftGameConfig(PapercraftLocalPlayer));

		hgeAnimation* Ship = CE.ResourceManager->GetAnimation("sprIdleShip");
		if(Ship != NULL)
		{
			AnimatedCharacter* ShipRO = new AnimatedCharacter();
			ShipRO->AddAnimation(*Ship);

			PapercraftShipComponentData& ShipData = *(new PapercraftShipComponentData());
			ShipData.Float(CMPID_X) = 100.0f;
			ShipData.Float(CMPID_Y) = 100.0f;

			ComponentSystem& System = *(new ComponentSystem(ShipData));

			Scene2DObject& SceneObject = *(new Scene2DObject());
			SceneObject.SetRenderObject(*ShipRO);
			SceneObject.SetComponentSystem(System);
			PapercraftLocalPlayer.AssociateSceneObject(SceneObject);
			World2D::Instance().AddPersistentObject(SceneObject, SOL_Foreground);
		}

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
