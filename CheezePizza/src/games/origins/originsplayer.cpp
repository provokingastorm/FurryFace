#include "cheezepizza.h"
#include "originsplayer.h"
#include "scene2dobject.h"
#include "originscomponentdata.h"

const float OriginsPlayer::VelocityPerSec = 135.0;
const float OriginsPlayer::MaxVelocity = 100.0f;

const float DefaultVelocity = 135.0f;

OriginsPlayer::OriginsPlayer()
	: SceneObject(NULL)
	, UpVelocity(VelocityPerSec)
	, DownVelocity(VelocityPerSec)
	, RightVelocity(VelocityPerSec)
	, LeftVelocity(VelocityPerSec)
{
}

OriginsPlayer::~OriginsPlayer()
{
	SceneObject = NULL;
}

void OriginsPlayer::AssociateSceneObject(Scene2DObject& PlayerObject)
{
	SceneObject = &PlayerObject;
}

void OriginsPlayer::DisassociateSceneObject()
{
	SceneObject = NULL;
}

void OriginsPlayer::OnCreatedInternal()
{
}

void OriginsPlayer::MoveUp(float DeltaTime)
{
	if(SceneObject != NULL)
	{
		const float Y = SceneObject->GetY();
		const float MoveDelta = (UpVelocity * DeltaTime);

		SceneObject->MoveVertical(Y - MoveDelta);
	}
}

void OriginsPlayer::MoveDown(float DeltaTime)
{
	if(SceneObject != NULL)
	{
		const float Y = SceneObject->GetY();
		const float MoveDelta = (DownVelocity * DeltaTime);

		SceneObject->MoveVertical(Y + MoveDelta);
	}
}

void OriginsPlayer::MoveLeft(float DeltaTime)
{
	if(SceneObject != NULL)
	{
		const float X = SceneObject->GetX();
		const float MoveDelta = (LeftVelocity * DeltaTime);

		SceneObject->MoveHorizontal(X - MoveDelta);
	}
}

void OriginsPlayer::MoveRight(float DeltaTime)
{
	if(SceneObject != NULL)
	{
		const float X = SceneObject->GetX();
		const float MoveDelta = (RightVelocity * DeltaTime);

		SceneObject->MoveHorizontal(X + MoveDelta);
	}
}

void OriginsPlayer::ResetVelocity()
{
	UpVelocity = VelocityPerSec;
	DownVelocity = VelocityPerSec;
	LeftVelocity = VelocityPerSec;
	RightVelocity = VelocityPerSec;
}