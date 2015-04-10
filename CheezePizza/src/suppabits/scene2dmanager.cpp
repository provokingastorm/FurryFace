#include "cheezepizza.h"
#include "scene2dmanager.h"
#include "scene2d.h"
#include "scene2dobject.h"
#include "cheezepizzaengine.h"

Scene2DManager::Scene2DManager()
	: CurrentScene(NULL)
{
}

Scene2DManager::~Scene2DManager()
{
}

void Scene2DManager::AddScene(class Scene2D& Scene, bool bIsCurrentScene)
{
	AddScene(Scene);

	if(bIsCurrentScene)
	{
		CurrentScene = &Scene;
	}
}

void Scene2DManager::AddScene(Scene2D& Scene)
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
	}
}

void Scene2DManager::AddPersistentObject(Scene2DObject& Object, ESceneObjectLayer DrawLayer)
{
	if(!HasPersistentObject(Object))
	{
		PersistentObjects[DrawLayer].push_back(&Object);
	}
}

bool Scene2DManager::HasPersistentObject(Scene2DObject& Object) const
{
	return (	
				HasPersistentObjectInLayer(Object, SOL_Background)
			||	HasPersistentObjectInLayer(Object, SOL_Layer1)
			||	HasPersistentObjectInLayer(Object, SOL_Layer2)
			||	HasPersistentObjectInLayer(Object, SOL_Foreground)
			);
}

bool Scene2DManager::HasPersistentObjectInLayer(Scene2DObject& Object, ESceneObjectLayer DrawLayer) const
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

void Scene2DManager::AddObjectsToRenderQueue(CheezePizzaEngine& Engine)
{
	AddLayerToRenderQueue(Engine, SOL_Background);
	AddLayerToRenderQueue(Engine, SOL_Layer1);
	AddLayerToRenderQueue(Engine, SOL_Layer2);
	AddLayerToRenderQueue(Engine, SOL_Foreground);
}

void Scene2DManager::AddLayerToRenderQueue(CheezePizzaEngine& Engine, ESceneObjectLayer DrawLayer)
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

void Scene2DManager::ShutdownInternal()
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
