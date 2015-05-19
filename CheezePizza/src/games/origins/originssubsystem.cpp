#include "cheezepizza.h"
#include "originssubsystem.h"
#include "originsplayerfactory.h"
#include "inputsubsystem.h"
#include "originsgameconfig.h"
#include "originsplayer.h"
#include "playersubsystem.h"
#include "sharedrenderables.h"
#include "cheezepizzaengine.h"
#include "world2d.h"
#include "scene2dobject.h"
#include "componentsystem.h"
#include "originscomponents.h"
#include "originscomponentdata.h"
#include "sharedcomponents.h"
#include "hgeresource.h"
#include "iplatform.h"

// ----------------------------------------------------------------------------
// Global function for the Cheeze Pizza Engine
// ----------------------------------------------------------------------------

IMPLEMENT_GAME_SUBSYSTEM_CREATOR(OriginsSubsystem);

// ----------------------------------------------------------------------------
// OriginsPlayerCreated - Definition
// ----------------------------------------------------------------------------

struct OriginsPlayerCreated : public DelegatePlayer
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
// OriginsSubsystem - Definition
// ----------------------------------------------------------------------------

void OriginsSubsystem::InitializeGameEngine(class IPlatform& Platform)
{
	CheezePizzaEngine& CE = CheezePizzaEngine::Instance();

	CE.Initialize(Platform, "Origins of Zelda", "Origins");

	CE.AddEngineSubsystem(InputSubsystem::Instance());
	CE.AddEngineSubsystem(PlayerSubsystem::Instance());
	CE.AddEngineSubsystem(World2D::Instance());
	CE.AddEngineSubsystem(*this);
}

void OriginsSubsystem::InitializeInternal()
{
	// Provide the engine with a factory that will create Origins-specific players
	OriginsPlayerFactory& Factory = *(new OriginsPlayerFactory());
	PlayerSubsystem::Instance().SetPlayerFactory(Factory);

	OriginsPlayerCreated& CreationDelegate = *(new OriginsPlayerCreated());
	PlayerSubsystem::Instance().AddPlayerCreatedDelegate(CreationDelegate);

	Scene2D& PrototypeScene = *(new Scene2D());

	hgeSprite* BGSprite = CheezePizzaEngine::Instance().ResourceManager->GetSprite("sprPrototypeBG");
	if(BGSprite != NULL)
	{
		FullscreenBackground* FullscreenRO = new FullscreenBackground();
		FullscreenRO->SetContent(*BGSprite);

		Scene2DObject& SceneObect = *(new Scene2DObject());
		SceneObect.SetRenderObject(*FullscreenRO);
		PrototypeScene.Add(SceneObect, SOL_Background);
	}

	World2D::Instance().AddScene(PrototypeScene, true);
}

void OriginsSubsystem::ShutdownInternal()
{
}