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
		RenderObject->SetHotSpot(Components->SharedData.Float(CMPID_X), Components->SharedData.Float(CMPID_Y));
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