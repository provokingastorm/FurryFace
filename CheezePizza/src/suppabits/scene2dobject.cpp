#include "cheezepizza.h"
#include "scene2dobject.h"
#include "sharedcomponents.h"
#include "irenderable.h"
#include <stdio.h>

Scene2DObject::Scene2DObject()
	: RenderObject(NULL)
	, OwnerData(NULL)
{
}

Scene2DObject::~Scene2DObject()
{
	if(RenderObject != NULL)
	{
		delete RenderObject;
		RenderObject = NULL;
	}

	if(OwnerData != NULL)
	{
		delete OwnerData;
		OwnerData = NULL;
	}
}

void Scene2DObject::SetRenderObject(IRenderable& Object)
{
	RenderObject = &Object;
}

void Scene2DObject::SetComponentData(class ComponentData& InData)
{
	OwnerData = &InData;
}

bool Scene2DObject::CanRender() const
{
	return RenderObject != NULL;
}

void Scene2DObject::Tick(float DeltaTime)
{
	if(RenderObject != NULL)
	{
		if(OwnerData != NULL)
		{
			RenderObject->SetHotSpot(OwnerData->Float(CMPID_X), OwnerData->Float(CMPID_Y));
		}

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

// EOF
