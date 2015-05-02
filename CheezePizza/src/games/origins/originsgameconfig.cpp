#include "cheezepizza.h"
#include "originsgameconfig.h"
#include "cheezepizzaengine.h"
#include "scene2dobject.h"
#include "localplayer.h"
#include <stdio.h>

const float OriginsGameConfig::VelocityPerSec = 0.01f;
const float OriginsGameConfig::MaxVelocity = 50.0f;

OriginsGameConfig::OriginsGameConfig()
	: InputConfig()
	, SceneObject(NULL)
	, MoveDistPerSec(5.0f)
	, UpVelocity(0.0f)
	, DownVelocity(0.0f)
	, RightVelocity(0.0f)
	, LeftVelocity(0.0f)
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
	KeyUpEvents.push_back(HGEK_W);
	KeyUpEvents.push_back(HGEK_A);
	KeyUpEvents.push_back(HGEK_S);
	KeyUpEvents.push_back(HGEK_D);
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

	case HGEK_W:
		UpVelocity = 0.0f;
		break;

	case HGEK_A:
		LeftVelocity = 0.0f;
		break;

	case HGEK_S:
		DownVelocity = 0.0f;
		break;

	case HGEK_D:
		RightVelocity = 0.0f;
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
		UpVelocity = MaxFloat(UpVelocity + VelocityPerSec, MaxVelocity);
		const float MoveDelta = Y * (UpVelocity * GetCachedDeltaTime());

		SceneObject->MoveVertical(Y - MoveDelta);
	}
}

void OriginsGameConfig::MoveDown()
{
	if(SceneObject != NULL)
	{
		const float Y = SceneObject->GetY();
		DownVelocity = MaxFloat(DownVelocity + VelocityPerSec, MaxVelocity);
		const float MoveDelta = Y * (DownVelocity * GetCachedDeltaTime());

		SceneObject->MoveVertical(Y + MoveDelta);
	}
}

void OriginsGameConfig::MoveLeft()
{
	if(SceneObject != NULL)
	{
		LeftVelocity = MaxFloat(LeftVelocity + VelocityPerSec, MaxVelocity);
		const float MoveDelta = MoveDistPerSec * (LeftVelocity * GetCachedDeltaTime());

		const float X = SceneObject->GetX();
		SceneObject->MoveHorizontal(X - MoveDelta);
	}
}

void OriginsGameConfig::MoveRight()
{
	if(SceneObject != NULL)
	{
		RightVelocity = MaxFloat(RightVelocity + VelocityPerSec, MaxVelocity);
		const float MoveDelta = MoveDistPerSec * (RightVelocity * GetCachedDeltaTime());

		const float X = SceneObject->GetX();
		SceneObject->MoveHorizontal(X + MoveDelta);
	}
}