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
	CPAssert(InData.SupportsData(CMPID_X),				"Scene2DObject: Attempting to assign a component data object that doesn't support CMPID_X data");
	CPAssert(InData.SupportsData(CMPID_Y),				"Scene2DObject: Attempting to assign a component data object that doesn't support CMPID_Y data");
	CPAssert(InData.SupportsData(CMPID_PartitionID),	"Scene2DObject: Attempting to assign a component data object that doesn't support CMPID_PartitionID data");

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

Vector2D Scene2DObject::GetPosition() const
{
	Vector2D Position(0.0f, 0.0f);

	if(OwnerData != NULL)
	{
		Position.X = OwnerData->Float(CMPID_X);
		Position.Y = OwnerData->Float(CMPID_Y);
	}

	return Position;
}

void Scene2DObject::SetPartition(int PartitionID)
{
	if(OwnerData != NULL)
	{
		OwnerData->Int(CMPID_PartitionID) = PartitionID;

		OnSetPartitionID(PartitionID);
	}
}

void Scene2DObject::QueueAction(int ActionType)
{

}

// EOF
