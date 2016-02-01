#include "cheezepizza.h"
#include "papercraftplayer.h"
#include "scene2dobject.h"

PapercraftPlayer::PapercraftPlayer()
	: SceneObject(NULL)
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

// EOF
