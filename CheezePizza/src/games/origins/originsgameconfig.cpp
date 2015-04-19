#include "cheezepizza.h"
#include "originsgameconfig.h"
#include "gamesession.h"
#include "scene2dobject.h"
#include "localplayer.h"

OriginsGameConfig::OriginsGameConfig(GameSession& AssignedSession, LocalPlayer& AssignedPlayer)
	: InputConfig(AssignedSession, AssignedPlayer)
	, SceneObject(NULL)
{
}

OriginsGameConfig::OriginsGameConfig(GameSession& AssignedSession)
	: InputConfig(AssignedSession)
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
		Session->GameOver();
		break;

	case HGEK_W:
		MoveUp(0.005f);
		break;

	case HGEK_A:
		MoveRight(0.005f);
		break;

	case HGEK_S:
		MoveLeft(0.005f);
		break;

	case HGEK_D:
		MoveDown(0.005f);
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

void OriginsGameConfig::MoveUp(float DeltaTime)
{
	if(SceneObject != NULL)
	{
		const int Y = SceneObject->GetY();
		const int MoveDelta = static_cast<int>(5.0f*DeltaTime);
		SceneObject->MoveVertical(Y + MoveDelta);
	}
}

void OriginsGameConfig::MoveDown(float DeltaTime)
{
	if(SceneObject != NULL)
	{
		const int Y = SceneObject->GetY();
		const int MoveDelta = static_cast<int>(5.0f*DeltaTime);
		SceneObject->MoveVertical(Y - MoveDelta);
	}
}

void OriginsGameConfig::MoveLeft(float DeltaTime)
{
	if(SceneObject != NULL)
	{
		const int X = SceneObject->GetX();
		const int MoveDelta = static_cast<int>(5.0f*DeltaTime);
		SceneObject->MoveHorizontal(X + MoveDelta);
	}
}

void OriginsGameConfig::MoveRight(float DeltaTime)
{
	if(SceneObject != NULL)
	{
		const int X = SceneObject->GetX();
		const int MoveDelta = static_cast<int>(5.0f*DeltaTime);
		SceneObject->MoveHorizontal(X - MoveDelta);
	}
}