#include "cheezepizza.h"
#include "originsgamesession.h"
#include "originsplayerfactory.h"
#include "inputsubsystem.h"
#include "originsgameconfig.h"
#include "originshud.h"
#include "originsplayer.h"
#include "originslinkrenderobject.h"
#include "sharedrenderables.h"
#include "cheezepizzaengine.h"
#include "world2d.h"
#include "scene2d.h"
#include "scene2dobject.h"
#include "hgeresource.h"

////////////////////////////////////////////////
// Global function for the Cheeze Pizza Engine
////////////////////////////////////////////////

IMPLEMENT_SESSION_CREATOR(OriginsGameSession)



////////////////////////////////////////////////
// OriginsGameSession definition
////////////////////////////////////////////////

OriginsGameSession::OriginsGameSession()
{
}

OriginsGameSession::~OriginsGameSession()
{
}

void OriginsGameSession::PreInit()
{
	if(HGEEngine != NULL)
	{
		// Provide the engine with a factory that will create Origins-specific players
		OriginsPlayerFactory* Factory = new OriginsPlayerFactory(*this);
		CheezeEngine->SetPlayerFactory(Factory);

		OriginsGameConfig* OriginsInput = new OriginsGameConfig(*this);
		CheezeEngine->InputSub->PushConfig(OriginsInput);

		// TODO - pbennett - 3/28/15 - Load game-specific INI files
	}
}

void OriginsGameSession::ShutdownInernal()
{
}

void OriginsGameSession::OnPlayerCreated(LocalPlayer& NewPlayer)
{
	CheezePizzaEngine& CE = (*CheezeEngine);
	Scene2DObject& Link = *(new Scene2DObject());

	hgeSprite* LinkSprite = CE.ResourceManager->GetSprite("sprLinkUp");
	if(LinkSprite != NULL)
	{
		OriginsLinkRenderObject& LinkRO = *(new OriginsLinkRenderObject());
		LinkRO.SetContent(*LinkSprite);
		Link.SetRenderObject(LinkRO);
	}

	//Manager.AddPersistentObject(Link, SOL_Foreground);
}

char* OriginsGameSession::GetGameName() const
{
	return "Origins of Zelda";
}

char* OriginsGameSession::GetGameShortName() const
{
	return "Origins";
}

void OriginsGameSession::LoadGame()
{
	CheezePizzaEngine& CE = (*CheezeEngine);

	if(CE.World != NULL)
	{
		Scene2D& PrototypeScene = *(new Scene2D());
		hgeSprite* BGSprite = CE.ResourceManager->GetSprite("sprPrototypeBG");
		if(BGSprite != NULL)
		{
			FullscreenBackground* FullscreenRO = new FullscreenBackground();
			FullscreenRO->SetContent(*BGSprite);

			Scene2DObject& SceneObect = *(new Scene2DObject());
			SceneObect.SetRenderObject(*FullscreenRO);
			PrototypeScene.Add(SceneObect, SOL_Background);
		}

		CE.World->AddScene(PrototypeScene, true);
	}
}