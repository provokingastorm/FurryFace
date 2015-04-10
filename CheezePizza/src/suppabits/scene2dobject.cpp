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