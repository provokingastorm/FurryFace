#include "cheezepizza.h"
#include "originsgamesession.h"
#include "originsplayerfactory.h"
#include "inputsubsystem.h"
#include "playersubsystem.h"
#include "originsgameconfig.h"
#include "originshud.h"
#include "originsplayer.h"
#include "originslinkrenderobject.h"
#include "sharedrenderables.h"
#include "cheezepizzaengine.h"
#include "world2d.h"
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
	// Provide the engine with a factory that will create Origins-specific players
	OriginsPlayerFactory& Factory = *(new OriginsPlayerFactory(*this));
	PlayerSubsystem::Instance().SetPlayerFactory(Factory);

	// TODO - pbennett - 3/28/15 - Load game-specific INI files
}

void OriginsGameSession::OnPlayerCreated(LocalPlayer& NewPlayer)
{
	CheezePizzaEngine& CE = CheezePizzaEngine::Instance();
	OriginsGameConfig& OriginsInput = *(new OriginsGameConfig());

	hgeAnimation* Link = CE.ResourceManager->GetAnimation("sprLink");
	if(Link != NULL)
	{
		AnimatedCharacter* LinkRO = new AnimatedCharacter();
		LinkRO->AddAnimation(*Link);

		Scene2DObject& SceneObject = *(new Scene2DObject());
		SceneObject.SetRenderObject(*LinkRO);
		OriginsInput.AssociateSceneObject(SceneObject);
		World2D::Instance().AddPersistentObject(SceneObject, SOL_Foreground);
	}

	InputSubsystem::Instance().PushConfig(OriginsInput);
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
	CheezePizzaEngine& CE = CheezePizzaEngine::Instance();
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

	World2D::Instance().AddScene(PrototypeScene, true);
}