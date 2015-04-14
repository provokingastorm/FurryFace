#include "cheezepizza.h"
#include "scene2dobject.h"
#include "irenderable.h"

Scene2DObject::Scene2DObject()
	: RenderObject(NULL)
{
}

Scene2DObject::~Scene2DObject()
{
	if(RenderObject != NULL)
	{
		delete RenderObject;
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