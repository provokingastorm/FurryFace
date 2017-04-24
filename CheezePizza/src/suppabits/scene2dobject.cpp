#include "cheezepizza.h"
#include "scene2dobject.h"
#include "scene2ddatatypes.h"
#include "irenderable.h"
#include <stdio.h>

Scene2DObject::Scene2DObject(Scene2DObjectData& InData)
	: ObjectData(InData)
{
}

Scene2DObject::~Scene2DObject()
{
	if(ObjectData.RenderObject != NULL)
	{
		delete ObjectData.RenderObject;
		ObjectData.RenderObject = NULL;
	}
}

class IRenderable* Scene2DObject::GetRenderObject() const
{
	return ObjectData.RenderObject;
}

void Scene2DObject::SetRenderObject(IRenderable& Object)
{
	ObjectData.RenderObject = &Object;
}

bool Scene2DObject::CanRender() const
{
	return ObjectData.RenderObject != NULL;
}

void Scene2DObject::Tick(float DeltaTime)
{
	if(ObjectData.RenderObject != NULL)
	{
		//ObjectData.RenderObject->SetHotSpot(ObjectData., OwnerData->Float(CMPID_Y));
		ObjectData.RenderObject->Tick(DeltaTime);
	}
}

void Scene2DObject::Start()
{
	if(ObjectData.RenderObject != NULL)
	{
		ObjectData.RenderObject->OnStart();
	}
}

void Scene2DObject::Stop()
{
	if(ObjectData.RenderObject != NULL)
	{
		ObjectData.RenderObject->OnStop();
	}
}

void Scene2DObject::Pause()
{
	if(ObjectData.RenderObject != NULL)
	{
		ObjectData.RenderObject->OnPause();
	}
}

Vector2D Scene2DObject::GetPosition() const
{
	Vector2D Position(0.0f, 0.0f);

	return Position;
}

void Scene2DObject::SetPartition(int PartitionID)
{
}

void Scene2DObject::QueueAction(int ActionType)
{

}

// EOF
