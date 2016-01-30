#include "cheezepizza.h"
#include "papercraftsubsystem.h"
#include "inputsubsystem.h"
#include "playersubsystem.h"
#include "world2d.h"
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
		CheezePizzaEngine& CE = CheezePizzaEngine::Instance();
		OriginsPlayer& OriginsLocalPlayer = static_cast<OriginsPlayer&>(Player);
		OriginsGameConfig& OriginsInput = *(new OriginsGameConfig(OriginsLocalPlayer));

		hgeAnimation* Link = CE.ResourceManager->GetAnimation("sprLink");
		if(Link != NULL)
		{
			AnimatedCharacter* LinkRO = new AnimatedCharacter();
			LinkRO->AddAnimation(*Link);

			OriginsLinkComponentData& LinkData = *(new OriginsLinkComponentData());
			LinkData.Float(CMPID_X) = 100.0f;
			LinkData.Float(CMPID_Y) = 100.0f;

			ComponentSystem& System = *(new ComponentSystem(LinkData));

			LinkComponent& LinkComp = *(new LinkComponent(System));

			Scene2DObject& SceneObject = *(new Scene2DObject());
			SceneObject.SetRenderObject(*LinkRO);
			SceneObject.SetComponentSystem(System);
			OriginsLocalPlayer.AssociateSceneObject(SceneObject);
			World2D::Instance().AddPersistentObject(SceneObject, SOL_Foreground);
		}

		InputSubsystem::Instance().PushConfig(OriginsInput);
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
