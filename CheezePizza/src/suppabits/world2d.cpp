#include "cheezepizza.h"
#include "world2d.h"
#include "scene2d.h"
#include "scene2dobject.h"
#include "cheezepizzaengine.h"

World2D::World2D()
	: CurrentScene(NULL)
{
}

World2D::~World2D()
{
}

void World2D::AddScene(class Scene2D& Scene, bool bIsCurrentScene)
{
	const bool bWasAdded = AddSceneInternal(Scene);

	if(bWasAdded && bIsCurrentScene)
	{
		CurrentScene = &Scene;
	}
}

bool World2D::AddSceneInternal(Scene2D& Scene)
{
	bool bAlreadyTracked = false;
	const int NumScenes = Scenes.size();

#if defined(_DEBUG)
	if(NumScenes <= 0)
	{
		// If CurrentScene is not NULL, the pointer was never NULL'd on init, cleared 
		// or somebody forgot to clear the pointer after removing the scene2d.
		CPAssert(CurrentScene == NULL, "The Scene2DManager has a CurrentScene without having any Scene2D!");
	}
#endif

	for(int i = 0; i < NumScenes; ++i)
	{
		if(Scenes[i] == &Scene)
		{
			bAlreadyTracked = true;
			break;
		}
	}

	if(!bAlreadyTracked)
	{
		Scenes.push_back(&Scene);
		return true;
	}

	return false;
}

void World2D::AddPersistentObject(Scene2DObject& Object, ESceneObjectLayer DrawLayer)
{
	if(!HasPersistentObject(Object))
	{
		PersistentObjects[DrawLayer].push_back(&Object);
	}
}

bool World2D::HasPersistentObject(Scene2DObject& Object) const
{
	return (	
				HasPersistentObjectInLayer(Object, SOL_Background)
			||	HasPersistentObjectInLayer(Object, SOL_Layer1)
			||	HasPersistentObjectInLayer(Object, SOL_Layer2)
			||	HasPersistentObjectInLayer(Object, SOL_Foreground)
			);
}

bool World2D::HasPersistentObjectInLayer(Scene2DObject& Object, ESceneObjectLayer DrawLayer) const
{
	CPAssert(DrawLayer != SOL_Max, "Scene2DManager::HasPersistentObjectInLayer() -  Using an invalid DrawLayer");

	const int NumObjs = PersistentObjects[DrawLayer].size();
	for(int i = 0; i < NumObjs; ++i)
	{
		if(PersistentObjects[DrawLayer][i] == &Object)
		{
			return true;
		}
	}

	return false;
}

void World2D::AddObjectsToRenderQueue(CheezePizzaEngine& Engine)
{
	AddLayerToRenderQueue(Engine, SOL_Background);
	AddLayerToRenderQueue(Engine, SOL_Layer1);
	AddLayerToRenderQueue(Engine, SOL_Layer2);
	AddLayerToRenderQueue(Engine, SOL_Foreground);
}

void World2D::AddLayerToRenderQueue(CheezePizzaEngine& Engine, ESceneObjectLayer DrawLayer)
{
	CPAssert(DrawLayer != SOL_Max, "Scene2DManager::AddLayerToRenderQueue() -  Using an invalid DrawLayer");

	// First, add objects associated to the given layer from the current visible scene
	if(CurrentScene != NULL)
	{
		CurrentScene->AddLayerToRenderQueue(Engine, DrawLayer);
	}

	// Now, add all persistent objects associated to the given layer
	const int NumObjs = PersistentObjects[DrawLayer].size();
	for(int i = 0; i < NumObjs; ++i)
	{
		Scene2DObject& SceneObject = (*PersistentObjects[DrawLayer][i]);
		IRenderable* RenderObject = SceneObject.GetRenderObject();

		if(RenderObject != NULL)
		{
			Engine.AddToRenderQueue(*RenderObject);
		}
	}
}

void World2D::ShutdownInternal()
{
	// Don't need to delete CurrentScene because it should be contained in the Scenes vector.
	CurrentScene = NULL;

	const int NumScenes = Scenes.size();
	for(int i = 0; i < NumScenes; ++i)
	{
		delete Scenes[i];
	}

	Scenes.clear();

	for(int j = 0; j < SOL_Max; ++j)
	{
		const int NumObjs = PersistentObjects[j].size();

		for(int h = 0; h < NumObjs; ++h)
		{
			delete PersistentObjects[j][h];
		}

		PersistentObjects[j].clear();
	}
}
