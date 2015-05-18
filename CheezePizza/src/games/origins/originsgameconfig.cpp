#include "cheezepizza.h"
#include "originsgameconfig.h"
#include "cheezepizzaengine.h"
#include "scene2dobject.h"
#include "localplayer.h"

const float OriginsGameConfig::VelocityPerSec = 135.0;
const float OriginsGameConfig::MaxVelocity = 100.0f;

const float DefaultVelocity = 135.0f;

OriginsGameConfig::OriginsGameConfig()
	: InputConfig()
	, SceneObject(NULL)
	, UpVelocity(VelocityPerSec)
	, DownVelocity(VelocityPerSec)
	, RightVelocity(VelocityPerSec)
	, LeftVelocity(VelocityPerSec)
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
		UpVelocity = VelocityPerSec;
	}
	if(HGEEngine.Input_KeyUp(HGEK_S))
	{
		DownVelocity = VelocityPerSec;
	}
	if(HGEEngine.Input_KeyUp(HGEK_A))
	{
		LeftVelocity = VelocityPerSec;
	}
	if(HGEEngine.Input_KeyUp(HGEK_D))
	{
		RightVelocity = VelocityPerSec;
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
		const float MoveDelta = (UpVelocity * DeltaTime);

		SceneObject->MoveVertical(Y - MoveDelta);
	}
}

void OriginsGameConfig::MoveDown(float DeltaTime)
{
	if(SceneObject != NULL)
	{
		const float Y = SceneObject->GetY();
		const float MoveDelta = (DownVelocity * DeltaTime);

		SceneObject->MoveVertical(Y + MoveDelta);
	}
}

void OriginsGameConfig::MoveLeft(float DeltaTime)
{
	if(SceneObject != NULL)
	{
		const float X = SceneObject->GetX();
		const float MoveDelta = (LeftVelocity * DeltaTime);

		SceneObject->MoveHorizontal(X - MoveDelta);
	}
}

void OriginsGameConfig::MoveRight(float DeltaTime)
{
	if(SceneObject != NULL)
	{
		const float X = SceneObject->GetX();
		const float MoveDelta = (RightVelocity * DeltaTime);

		SceneObject->MoveHorizontal(X + MoveDelta);
	}
}