#include "cheezepizza.h"
#include "scene2dobject.h"
#include "irenderable.h"
#include <stdio.h>

Scene2DObject::Scene2DObject()
	: RenderObject(NULL)
	, Position(0.0f, 0.0f)
{
}

Scene2DObject::~Scene2DObject()
{
	if(RenderObject != NULL)
	{
		delete RenderObject;
		RenderObject = NULL;
	}
}

void Scene2DObject::SetRenderObject(IRenderable& Object)
{
	RenderObject = &Object;
}

bool Scene2DObject::CanRender() const
{
	return RenderObject != NULL;
}

void Scene2DObject::Tick(float DeltaTime)
{
	if(RenderObject != NULL)
	{
		RenderObject->SetHotSpot(Position.X, Position.Y);
		RenderObject->Tick(DeltaTime);
	}
}

void Scene2DObject::Start()
{
	if(RenderObject != NULL)
	{
		RenderObject->OnStart();
	}
}

void Scene2DObject::Stop()
{
	if(RenderObject != NULL)
	{
		RenderObject->OnStop();
	}
}

void Scene2DObject::Pause()
{
	if(RenderObject != NULL)
	{
		RenderObject->OnPause();
	}
}

void Scene2DObject::Move(float NewX, float NewY)
{
	printf("Moving Vertical: %f", NewY);
	printf("Moving Horizontal: %f", NewX);
	Position.X = NewX;
	Position.Y = NewY;
}

void Scene2DObject::MoveVertical(float NewY)
{
	printf("Moving Vertical: %f", NewY);
	Position.Y = NewY;
}

void Scene2DObject::MoveHorizontal(float NewX)
{
	printf("Moving Horizontal: %f", NewX);
	Position.X = NewX;
}
