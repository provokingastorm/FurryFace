#include "cheezepizza.h"
#include "originsgameconfig.h"
#include "cheezepizzaengine.h"
#include "scene2dobject.h"
#include "localplayer.h"
#include <stdio.h>

OriginsGameConfig::OriginsGameConfig()
	: InputConfig()
	, SceneObject(NULL)
	, MoveDistPerSec(150.0f)
{
}

OriginsGameConfig::OriginsGameConfig(LocalPlayer& AssignedPlayer)
	: InputConfig(AssignedPlayer)
	, SceneObject(NULL)
{
}

OriginsGameConfig::~OriginsGameConfig()
{
	SceneObject = NULL;
}

void OriginsGameConfig::GetKeyUpEvents(std::vector<int>& KeyUpEvents)
{
	KeyUpEvents.push_back(HGEK_ESCAPE);
}

void OriginsGameConfig::GetKeyDownEvents(std::vector<int>& KeyUpEvents)
{
	KeyUpEvents.push_back(HGEK_W);
	KeyUpEvents.push_back(HGEK_A);
	KeyUpEvents.push_back(HGEK_S);
	KeyUpEvents.push_back(HGEK_D);
}

void OriginsGameConfig::OnKeyUp(int KeyID)
{
	switch(KeyID)
	{
	case HGEK_ESCAPE:
		CheezePizzaEngine::Instance().ExitApplication();
		break;

	default:
		break;
	}
}

void OriginsGameConfig::OnKeyDown(int KeyID)
{
	switch(KeyID)
	{
	case HGEK_W:
		MoveUp();
		break;

	case HGEK_A:
		MoveLeft();
		break;

	case HGEK_S:
		MoveDown();
		break;

	case HGEK_D:
		MoveRight();
		break;

	default:
		break;
	}
}

void OriginsGameConfig::AssociateSceneObject(class Scene2DObject& PlayerObject)
{
	SceneObject = &PlayerObject;
}

void OriginsGameConfig::DisassociateSceneObject()
{
	SceneObject = NULL;
}

void OriginsGameConfig::MoveUp()
{
	if(SceneObject != NULL)
	{
		const float Y = SceneObject->GetY();
		const float MoveDelta = MoveDistPerSec * GetCachedDeltaTime();
		SceneObject->MoveVertical(Y - MoveDelta);
	}
}

void OriginsGameConfig::MoveDown()
{
	if(SceneObject != NULL)
	{
		const float Y = SceneObject->GetY();
		const float MoveDelta = MoveDistPerSec * GetCachedDeltaTime();
		SceneObject->MoveVertical(Y + MoveDelta);
	}
}

void OriginsGameConfig::MoveLeft()
{
	if(SceneObject != NULL)
	{
		const float X = SceneObject->GetX();
		const float MoveDelta = MoveDistPerSec * GetCachedDeltaTime();
		SceneObject->MoveHorizontal(X - MoveDelta);
	}
}

void OriginsGameConfig::MoveRight()
{
	if(SceneObject != NULL)
	{
		const float X = SceneObject->GetX();
		const float MoveDelta = MoveDistPerSec * GetCachedDeltaTime();
		SceneObject->MoveHorizontal(X + MoveDelta);
	}
}