#include "cheezepizza.h"
#include "originsgameconfig.h"
#include "cheezepizzaengine.h"
#include "scene2dobject.h"
#include "localplayer.h"
#include <stdio.h>

const float OriginsGameConfig::VelocityPerSec = 0.01f;
const float OriginsGameConfig::MaxVelocity = 100.0f;

OriginsGameConfig::OriginsGameConfig()
	: InputConfig()
	, SceneObject(NULL)
	, MoveDistPerSec(150.0f)
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

void OriginsGameConfig::HandleInput(float DeltaTime)
{
	HGE& HGEEngine = CheezePizzaEngine::Instance().GetHGE();

	if(HGEEngine.Input_GetKeyState(HGEK_ESCAPE))
	{
		CheezePizzaEngine::Instance().ExitApplication();
	}

	if(HGEEngine.Input_GetKeyState(HGEK_W))
	{
		MoveUp(DeltaTime);
	}
	else if(HGEEngine.Input_GetKeyState(HGEK_S))
	{
		MoveDown(DeltaTime);
	}
	else if(HGEEngine.Input_GetKeyState(HGEK_A))
	{
		MoveLeft(DeltaTime);
	}
	else if(HGEEngine.Input_GetKeyState(HGEK_D))
	{
		MoveRight(DeltaTime);
	}

	if(HGEEngine.Input_KeyUp(HGEK_W))
	{
		UpVelocity = 0.0f;
	}
	if(HGEEngine.Input_KeyUp(HGEK_S))
	{
		DownVelocity = 0.0f;
	}
	if(HGEEngine.Input_KeyUp(HGEK_A))
	{
		LeftVelocity = 0.0f;
	}
	if(HGEEngine.Input_KeyUp(HGEK_D))
	{
		RightVelocity = 0.0f;
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
		const float Y = SceneObject->GetY();
		const float MoveDelta = MoveDistPerSec * DeltaTime;

		SceneObject->MoveVertical(Y - MoveDelta);
	}
}

void OriginsGameConfig::MoveDown(float DeltaTime)
{
	if(SceneObject != NULL)
	{
		const float Y = SceneObject->GetY();
		const float MoveDelta = MoveDistPerSec * DeltaTime;

		SceneObject->MoveVertical(Y + MoveDelta);
	}
}

void OriginsGameConfig::MoveLeft(float DeltaTime)
{
	if(SceneObject != NULL)
	{
		const float X = SceneObject->GetX();
		const float MoveDelta = MoveDistPerSec * DeltaTime;

		SceneObject->MoveHorizontal(X - MoveDelta);
	}
}

void OriginsGameConfig::MoveRight(float DeltaTime)
{
	if(SceneObject != NULL)
	{
		const float X = SceneObject->GetX();
		const float MoveDelta = MoveDistPerSec * DeltaTime;

		SceneObject->MoveHorizontal(X + MoveDelta);
	}
}