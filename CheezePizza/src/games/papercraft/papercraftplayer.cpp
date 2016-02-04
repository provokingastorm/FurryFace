#include "cheezepizza.h"
#include "papercraftplayer.h"
#include "papercraftcomponentdata.h"
#include "scene2dobject.h"
#include "componentdata.h"

const float PapercraftPlayer::VelocityPerSec = 135.0;
const float PapercraftPlayer::MaxVelocity = 100.0f;

const float DefaultVelocity = 135.0f;

PapercraftPlayer::PapercraftPlayer()
	: SceneObject(NULL)
	, UpVelocity(VelocityPerSec)
	, DownVelocity(VelocityPerSec)
	, RightVelocity(VelocityPerSec)
	, LeftVelocity(VelocityPerSec)
{
}

PapercraftPlayer::~PapercraftPlayer()
{
	SceneObject = NULL;
}

void PapercraftPlayer::AssociateSceneObject(Scene2DObject& PlayerObject)
{
	SceneObject = &PlayerObject;
}

void PapercraftPlayer::DisassociateSceneObject()
{
	SceneObject = NULL;
}

void PapercraftPlayer::OnCreatedInternal()
{
}

void PapercraftPlayer::MoveUp(float DeltaTime)
{
	if(SceneObject != NULL)
	{
		float& Y = SceneObject->GetData().Float(CMPID_Y);
		const float MoveDelta = (UpVelocity * DeltaTime);
		Y = Y - MoveDelta;
	}
}

void PapercraftPlayer::MoveDown(float DeltaTime)
{
	if(SceneObject != NULL)
	{
		float& Y = SceneObject->GetData().Float(CMPID_Y);
		const float MoveDelta = (DownVelocity * DeltaTime);
		Y = Y + MoveDelta;
	}
}

void PapercraftPlayer::MoveLeft(float DeltaTime)
{
	if(SceneObject != NULL)
	{
		float& X = SceneObject->GetData().Float(CMPID_X);
		const float MoveDelta = (LeftVelocity * DeltaTime);
		X = X - MoveDelta;
	}
}

void PapercraftPlayer::MoveRight(float DeltaTime)
{
	if(SceneObject != NULL)
	{
		float& X = SceneObject->GetData().Float(CMPID_X);
		const float MoveDelta = (RightVelocity * DeltaTime);
		X = X + MoveDelta;
	}
}

void PapercraftPlayer::ResetVelocity()
{
	UpVelocity = VelocityPerSec;
	DownVelocity = VelocityPerSec;
	LeftVelocity = VelocityPerSec;
	RightVelocity = VelocityPerSec;
}

// EOF
