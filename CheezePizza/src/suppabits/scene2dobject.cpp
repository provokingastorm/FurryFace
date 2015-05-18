#include "cheezepizza.h"
#include "scene2dobject.h"
#include "componentsystem.h"
#include "sharedcomponents.h"
#include "irenderable.h"
#include <stdio.h>

Scene2DObject::Scene2DObject()
	: RenderObject(NULL)
	, Components(NULL)
{
}

Scene2DObject::~Scene2DObject()
{
	if(RenderObject != NULL)
	{
		delete RenderObject;
		RenderObject = NULL;
	}

	if(Components != NULL)
	{
		delete Components;
		Components = NULL;
	}
}

void Scene2DObject::SetRenderObject(IRenderable& Object)
{
	RenderObject = &Object;
}

void Scene2DObject::SetComponentSystem(class ComponentSystem& System)
{
	Components = &System;
}

bool Scene2DObject::CanRender() const
{
	return RenderObject != NULL;
}

void Scene2DObject::Tick(float DeltaTime)
{
	if(RenderObject != NULL)
	{
		RenderObject->SetHotSpot(GetX(), GetY());
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

ComponentData& Scene2DObject::GetData() const
{
	return Components->SharedData;
}

float Scene2DObject::GetX() const
{
	float X = 0.0f;
	Components->SharedData.GetFloat(CMPID_X, X);
	return X;
}

float Scene2DObject::GetY() const
{
	float Y = 0.0f;
	Components->SharedData.GetFloat(CMPID_Y, Y);
	return Y;
}

void Scene2DObject::Move(float NewX, float NewY)
{
	Components->SharedData.SetFloat(CMPID_X, NewX);
	Components->SharedData.SetFloat(CMPID_Y, NewY);
}

void Scene2DObject::MoveVertical(float NewY)
{
	Components->SharedData.SetFloat(CMPID_Y, NewY);
}

void Scene2DObject::MoveHorizontal(float NewX)
{
	Components->SharedData.SetFloat(CMPID_X, NewX);
}
