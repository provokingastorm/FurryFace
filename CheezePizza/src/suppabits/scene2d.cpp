#include "cheezepizza.h"
#include "scene2d.h"
#include "scene2dobject.h"
#include "cheezepizzaengine.h"
#include "hgeresource.h"

Scene2D::Scene2D()
{
}

Scene2D::~Scene2D()
{
	for(int DrawLayer = 0; DrawLayer < SOL_Max; ++DrawLayer)
	{
		const int NumObjects = SceneObjects[DrawLayer].size();
		for(int i = 0; i < NumObjects; ++i)
		{
			delete SceneObjects[DrawLayer][i];
		}

		SceneObjects[DrawLayer].clear();
	}
}

void Scene2D::Add(Scene2DObject& Object , ESceneObjectLayer DrawLayer)
{
	if(!HasSceneObject(Object, DrawLayer))
	{
		SceneObjects[DrawLayer].push_back(&Object);
	}
}

void Scene2D::AddLayerToRenderQueue(ESceneObjectLayer DrawLayer)
{
	CPAssert(DrawLayer != SOL_Max, "");

	const int NumObjects = SceneObjects[DrawLayer].size();
	for(int i = 0; i < NumObjects; ++i)
	{
		IRenderable* RenderObject = SceneObjects[DrawLayer][i]->GetRenderObject();

		if(RenderObject != NULL)
		{
			CheezePizzaEngine::Instance().AddToRenderQueue(*RenderObject);
		}
	}
}

void Scene2D::EnterScene()
{
	for(int i = 0; i < SOL_Max; ++i)
	{
		const int DrawLayer = i;
		const int NumObjects = SceneObjects[i].size();

		for(int j = 0; j < NumObjects; ++j)
		{
			SceneObjects[i][j]->Start();
		}
	}
}

void Scene2D::ExitScene()
{
	for(int i = 0; i < SOL_Max; ++i)
	{
		const int DrawLayer = i;
		const int NumObjects = SceneObjects[i].size();

		for(int j = 0; j < NumObjects; ++j)
		{
			SceneObjects[i][j]->Stop();
		}
	}
}

bool Scene2D::HasSceneObject(Scene2DObject& Object)
{
	return ( HasSceneObject(Object, SOL_Background) || HasSceneObject(Object, SOL_Layer1) || HasSceneObject(Object, SOL_Layer2) || HasSceneObject(Object, SOL_Foreground) );
}

bool Scene2D::HasSceneObject(Scene2DObject& Object, ESceneObjectLayer DrawLayer)
{
	bool bHasObject = false;

	const int NumObjects = SceneObjects[DrawLayer].size();
	for(int i = 0; i < NumObjects; ++i)
	{
		if(SceneObjects[DrawLayer][i] == &Object)
		{
			bHasObject = true;
			break;
		}
	}

	return bHasObject;
}
